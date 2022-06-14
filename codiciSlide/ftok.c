#include <sys/ipc.h>
#include <stdio.h>

int main(){
    key_t coda1=ftok("/tmp/unique",1);
    key_t coda2=ftok("/tmp/unique",2);
    printf("Le chiavi sono %d e %d\n",coda1,coda2);
    return 0;
}