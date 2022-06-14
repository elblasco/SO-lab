#include<stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
    char *nomeFile[]={"sebastiani.txt","errori.txt","input.txt"};
    for (int i=1;i<argc;++i) {
        int fid=fork();
        while(wait(NULL)>0);
        if(fid==0){
            int file=open(nomeFile[0],O_RDWR|O_CREAT,S_IREAD|S_IWRITE),
                error=open(nomeFile[1],O_RDWR|O_CREAT,S_IREAD|S_IWRITE);
            dup2(file, STDOUT_FILENO);
            dup2(error,STDERR_FILENO);
            execl(argv[i],argv[i],NULL);
            close(file);
            close(error);
        }
    }
    printf("Ho finito tutti i fork\n");
    return 0;
}