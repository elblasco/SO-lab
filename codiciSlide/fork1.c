#include <stdio.h>
#include <unistd.h>

int main(){
    fork();
    fork();
    fork();
    printf("Ciao mondo\n");
    return 0;
}