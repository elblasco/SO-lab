#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX 255

int main(){
    int openFile=open("sebastiani.txt",O_RDONLY);
    char contenuto[MAX];
    int byteLetti;
    do {
        byteLetti=read(openFile,contenuto,2); //read 9 bytes from openFile and put them in contenuto
        contenuto[byteLetti]=0; //adding a closing byte
        printf("%s",contenuto);
    }while (byteLetti>0);
    return 0;
}