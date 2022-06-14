#include<stdio.h>
#include<unistd.h>

int main(){
    char buffer[255];
    printf("The currenti directory is:\n%s\n",getcwd(buffer,255));
    return 0;
}