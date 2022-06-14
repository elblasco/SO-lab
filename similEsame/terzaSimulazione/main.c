#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAXLEN 256

FILE *in;
int caratteri=0,linee=0;

void file_check( char * path){
    in= fopen(path,"r");
    if(in==NULL){
        fprintf(stderr,"File non aperto\n");
        exit(1);
    }
}

void logica_figlio(int argc,char ** argv){
    if(argc==3){
        while(feof(in)==0){
            char c= getc(in);
            if(c=='\n'){
                linee++;
            }
            else{
                caratteri++;
            }
        }
        if(strcmp(argv[1],"-l")==0){
            fprintf(stdout,"%d\n",linee);
        }
        else{
            fprintf(stdout,"%d\n",caratteri-1);
        }
    }
    else{
        while(feof(in)==0){
            char c= getc(in);
            if(c=='\n'){
                linee++;
            }
            else{
                caratteri++;
            }
        }
        if(strcmp(argv[1],"-c")==0 && strcmp(argv[2],"-c")==0){
            fprintf(stdout,"%d %d\n",caratteri-1,linee);
        }
        else{
            fprintf(stdout,"%d %d\n",linee,caratteri-1);
        }
    }
}

void logica_pipe(int argc,char ** argv){
    char tmp;
    while(read(STDIN_FILENO,&tmp,1)>0){
        if(tmp=='\n'){
            linee++;
        }
        else{
            caratteri++;
        }
    }
    caratteri--;
    if(argc==3){
        if(strcmp(argv[1],"-l")==0 && strcmp(argv[2],"-c")==0){
            printf("%d %d\n",linee,caratteri);
        }
        else if(strcmp(argv[1],"-c")==0 && strcmp(argv[2],"-l")==0){
            printf("%d %d\n",caratteri,linee);
        }
    }
    else{
        if(strcmp(argv[1],"-c")==0){
            printf("%d\n",caratteri);
        }
        else if(strcmp(argv[1],"-l")==0){
            printf("%d\n",linee);
        }
    }
}

void arg_check(int argc, char **argv){
    if(argc<2 || argc>4){
        fprintf(stderr,"Argomenti errati\n");
        exit(2);
    }
    else if(!isatty(fileno(stdin)) &&
            (strcmp(argv[1],"-c")==0 || strcmp(argv[1],"-l")==0) ||
            (strcmp(argv[1],"-l")==0 && strcmp(argv[2],"-c")==0) ||
            (strcmp(argv[1],"-c")==0 && strcmp(argv[2],"-l")==0)){
        int figlio=fork();
        if(figlio==0){
            logica_pipe(argc,argv);
        }
        else if(figlio>0){
            while(wait(NULL)>0);
        }
        else{
            fprintf(stderr,"Figlio non creato\n");
        }
    }
    else if((strcmp(argv[1],"-l")==0 && strlen(argv[2])<=2) ||
            (strcmp(argv[1],"-c")==0 && strlen(argv[2])<=2)){
        fprintf(stderr,"Argomenti errati\n");
        exit(3);
    }
    else if((strcmp(argv[1],"-l")==0 && strcmp(argv[2],"-c")==0) ||
            strcmp(argv[1],"-c")==0 && strcmp(argv[2],"-l")==0){
        file_check(argv[3]);
        int figlio=fork();
        if(figlio==0){
            logica_figlio(argc,argv);
        }
        else if(figlio>0){
            while(wait(NULL)>0);
        }
        else{
            fprintf(stderr,"Figlio non creato\n");
            exit(4);
        }
    }
    else if((strcmp(argv[1],"-l")==0 && strlen(argv[2])>2) ||
            (strcmp(argv[1],"-c")==0 && strlen(argv[2])>2)){
        file_check(argv[2]);
        int figlio=fork();
        if(figlio==0){
            logica_figlio(argc,argv);
        }
        else if(figlio>0){
            while(wait(NULL)>0);
        }
        else{
            fprintf(stderr,"Figlio non creato\n");
            exit(4);
        }
    }
    else{
        fprintf(stderr,"Argomenti errati\n");
        exit(5);
    }
}

int main(int argc, char ** argv) {
    arg_check(argc,argv);
    return 0;
}
