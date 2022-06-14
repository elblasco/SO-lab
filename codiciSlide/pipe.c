#include <stdio.h> //pipe.c
#include <unistd.h>
#include <fcntl.h>

int main(){
    int vet[2],cnt=0;
    while (pipe(vet)==0){
        cnt++;
        printf("%d %d\n",vet[0],vet[1]);
    }
    printf("Opened %d pipes, then error\n",cnt);
    int op = open("/tmp/tmp.txt",O_CREAT|O_RDWR,S_IRUSR|S_IWUSR);
    printf("File opened with fd %d\n",op);
    return 0;
}