#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
    int file=open("sebastiani.txt",O_RDONLY);
    fchown(file,0,0);
    chmod("sebastani.txt",S_IRUSR|S_IRGRP|S_IROTH);
    return 0;
}