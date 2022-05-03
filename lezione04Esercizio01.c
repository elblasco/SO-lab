#include<stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
    char *nomeFile[]={"sebastiani.txt","errori.txt"};
    for (int i=1;i<argc;++i) {
        int fid=fork();
        while(wait(NULL)>0);
        if(fid==0){
            execl(argv[i],argv[i],NULL);
        }
    }
    printf("Ho finito tutti i fork\n");
    return 0;
}