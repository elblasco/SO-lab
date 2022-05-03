#include<string.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int file=open("sebastiani.txt",O_RDWR);
    char daScrivere[]="Sebastiani chad\n";
    write(file,"Ciao caccola\n",strlen("Ciao caccola\n"));
    lseek(file,10,SEEK_SET); //reposition the I/0 pointer
    write(file,daScrivere,strlen(daScrivere));
    return 0;
}