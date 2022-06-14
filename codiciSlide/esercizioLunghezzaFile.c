#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int lunghezzaByte(int fd){
    int size=lseek(fd,SEEK_SET,SEEK_END);
    return size;
}

int main(){
    int file=open("sebastiani.txt",O_RDONLY);
    printf("%d\n",lunghezzaByte(file));
    close(file);
    return 0;
}