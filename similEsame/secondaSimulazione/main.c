#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>

#define MAXARG 3
#define MAXCHILD 10
#define CHAREAD 6

typedef enum {
    KP_ECHO_OFF,
    KP_ECHO_ON,
} kp_echo_t;

struct sigaction sa;
FILE* out;
FILE* in;
int figli[MAXCHILD],counterFigli=0,contatoreClient=0,pid_letto;

void scriveFiglio(){
    fprintf(out,"+%d",getpid());
    fflush(out);
}

void clientHandler(int signo){
    if(signo==SIGINT){
        exit(0);
    }
}

void handler(int signo){
    if(signo==SIGUSR1){
        int figlio=fork();
        if(figlio==0){
            scriveFiglio();
            while (1){
                pause();
            }
            
        }
        else{
            figli[counterFigli]=figlio;
            counterFigli++;
            printf("+[server] %d\n",figli[counterFigli-1]);
            fflush(stdout);
        }
    }
    else if(signo==SIGUSR2){
        if(counterFigli==0){
            fprintf(out,"-0\n");
            fflush(out);
            printf("-[server] 0\n");
            fflush(stdout);
        }
        else{
            fprintf(out,"-%d\n",figli[counterFigli-1]);
            fflush(out);
            printf("-[server] %d\n",figli[counterFigli-1]);
            fflush(stdout);
            kill(figli[counterFigli-1],SIGKILL);
            --counterFigli;
        }
    }
    else if(signo==SIGINT){
        fprintf(out,"%d",counterFigli);
        fflush(out);
    }
    else{
        perror("segnale non gestito");
        exit(3);
    }
}

int keypress(const kp_echo_t echo) {
    struct termios savedState, newState;
    unsigned char echo_bit; // flag
    int c;
    if (-1 == tcgetattr(STDIN_FILENO, &savedState)) { return EOF; }; // error
    newState = savedState;
    if (KP_ECHO_OFF == echo) { echo_bit = ECHO; } else { echo_bit = 0; };
    /* canonical input + set echo with minimal input as 1. */
    newState.c_lflag &= ~(echo_bit | ICANON);
    newState.c_cc[VMIN] = 1;
    if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &newState)) { return EOF; }; // error
    c = getchar(); /* block until key press */
    if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &savedState)) { return EOF; }; // error
    return c;
}

FILE *w_fopen(const char * nome,const char* mod){
    FILE *ret=fopen(nome,mod);
    if(ret==NULL){
        perror("Non sopno riuscito ad aprire il file");
        exit(2);
    }
    else{
        return ret;
    }
}

void get_pid(){
    fscanf(in,"%d\n",&pid_letto);
    printf("%d\n",pid_letto);
}

void w_client(const int signo,const int pausa){
    if(signo==SIGUSR1 && contatoreClient<9){
        contatoreClient++;
        kill(pid_letto,signo);
        sleep(pausa);
    }
    else if(signo==SIGUSR2 && contatoreClient>0){
        contatoreClient--;
        kill(pid_letto,signo);
        sleep(pausa);
    }
}

int main(int argc,char ** argv){
    if(argc!=MAXARG){
        fprintf(stderr,"Numero argomenti errato\n");
        exit(2);
    }
    else{
        if(strcmp(argv[1],"server")==0){
            sa.sa_handler = handler;
            sigemptyset(&sa.sa_mask);
            sigaction(SIGUSR1,&sa,NULL);
            sigaction(SIGUSR2,&sa,NULL);
            sigaction(SIGINT,&sa,NULL);
            out=w_fopen(argv[2],"w+");
            fprintf(out,"%d\n",getpid());
            fflush(out);
            printf("[server:%d]\n",getpid());
            while(1){
                pause();
            };
        }
        else{
            
            sa.sa_handler=clientHandler;
            sigemptyset(&sa.sa_mask);
            sigaction(SIGINT,&sa,NULL);
            char buffer[CHAREAD];
            while(in==NULL){
                in=w_fopen(argv[2],"r+");
            }
            get_pid();
            printf("Sono qua con il pid del server a %d\n",pid_letto);
            char c;
            while (1) {
                c = keypress(KP_ECHO_OFF); // read single keypress without echoing
                if (c=='+') {
                    printf("PLUS\n");
                    w_client(SIGUSR1,0);
                }
                if (c=='-') {
                    printf("MINUS\n");
                    w_client(SIGUSR2,0);
                }
                if (c=='\n') {
                    printf("ENTER\n");
                    while(contatoreClient>0){
                        w_client(SIGUSR2,1);
                    }
                }
            }
        }
    }
    return 0;
}