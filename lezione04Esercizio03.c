#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char ** argv){
    char *nomeFile[]={"sebastiani.txt","errori.txt","input.txt"};
    int fid=fork();
    while(wait(NULL)>0);
    if(fid==0){
        int out=open(nomeFile[2],O_WRONLY|O_CREAT,S_IREAD|S_IWRITE),
            err=open(nomeFile[1],O_WRONLY|O_CREAT,S_IREAD|S_IWRITE);
        dup2(out, STDOUT_FILENO);
        dup2(err,STDERR_FILENO);
        system(argv[1]);
        close(out);
        close(err);
    }
    else{
        int in=open(nomeFile[2],O_RDWR),
            err=open(nomeFile[1],O_APPEND),
            out=open(nomeFile[0],O_WRONLY|O_CREAT,S_IREAD|S_IWRITE);
        dup2(out, STDOUT_FILENO);
        dup2(err,STDERR_FILENO);
        dup2(in,STDIN_FILENO);
        system(argv[2]);
        close(in);
        close(err);
        close(out);
    }
    return 0;
}