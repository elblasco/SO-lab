#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void main(){
    int output=open("./sebastiani.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
    printf("%d\n",output);
    dup2(output,1);
    char * argomenti[]={"./time.out",NULL};
    execvp(argomenti[0],argomenti);
}