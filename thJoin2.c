#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*
Grazie Naimoli questo programma non stampa un cazzo
*/

void *fun1(void * parametro){
    sleep(2);
}

void * fun2(void *parametro){
    if(pthread_join(*(pthread_t *)parametro,NULL)!=0){
        perror("Errore: ");
    }
}

int main(){
    pthread_t tId1,tId2;
    pthread_create(&tId1,NULL,fun1,NULL); //Crea un primo thread
    pthread_create(&tId2,NULL,fun2,(void *)&tId1); //Crea un secondo thread
    pthread_join(tId1,NULL); //Aspetta il primo thread
    sleep(1);
    perror("Errore mel main: ");
}