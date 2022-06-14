#include <stdio.h>
#include <string.h>
#define SIZE 255

int main(){
    char buffer[SIZE];
    fgets(buffer,sizeof(buffer),stdin);
    printf("%s",buffer);
    return 0;
}