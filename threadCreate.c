#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *funzione(void *parametro){
    printf("Questo è un thread che ha ricevuto %d\n",*(int *)parametro);
    return (void *)3;
}

int main(){
    pthread_t tId;
    int arg=10;
    pthread_create(&tId,NULL,funzione,(void *)&arg);
    printf("Ho eseguito un thread con id %ld\n",tId);
    return 0;
}