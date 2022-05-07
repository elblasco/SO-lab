#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
    int fd;
    char *pathFifo="/tmp/fifo1";
    int ret=mkfifo(pathFifo,S_IRUSR|S_IWUSR);
    printf("La mkfifo ha risultato %d\n",ret);
    char str1[80], *str2="Sono il lettore";
    fd=open(pathFifo,O_RDONLY);
    printf("la open ha coidce %d\n",fd);
    read(fd,str1,80);
    close(fd);
    printf("Lo scrittore sta scrivendo %s\n",str1);
    fd=open(pathFifo,O_WRONLY);
    write(fd,str2,strlen(str2)+1);
    close(fd);
    return 0;
}