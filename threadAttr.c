/*
NB: un thread detached non può diventare joinable durante la sua esecuzione,
mentre il contrario è possibile.
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *funzione(void *paramentro){
    printf("Questo è un thread che ha ricevuto %d\n",*(int *)paramentro);
    return (void *)3;
}

int main(){
    pthread_t tId;
    pthread_attr_t attr;
    int arg=10, statoDetach;
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED); // Set del fatto che il thread e detach
    pthread_attr_getdetachstate(&attr,&statoDetach); // Assegna alla  variabile statoDetach lo stato
    if(statoDetach==PTHREAD_CREATE_DETACHED){
        printf("Detached\n");
    }
    pthread_create(&tId,&attr,funzione,(void *)&arg);
    printf("Ho eseguito il thread con id %ld\n",tId);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE); //Istruzione che in questo caso non ha effetto
    sleep(3);
    int esito=pthread_join(tId,(void **)&statoDetach);
    printf("Terminato con esito %d\n",esito);
    return 0;
}