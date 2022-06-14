#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int i=1; //E' facile far comunicare i thread basta usare varabili globali

void * funzione(void * parametro){
    if(i--){
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL); //Cambia la modalità del thread
    }
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL); //Cambia lo stato del thread
    printf("Thread %ld partito\n",*(pthread_t *)parametro);
    sleep(3);
    printf("Thread %ld terminato\n",*(pthread_t *)parametro);
}

int main(){
    pthread_t tId1,tId2;
    pthread_create(&tId1,NULL,funzione,(void *)&tId1); //Crea un primo thread
    sleep(1);
    pthread_cancel(tId1); //Cancella il thread
    printf("Ho mandato la richiesta per la cancellazione del thread %ld\n",&tId1);
    pthread_create(&tId2,NULL,funzione,(void *)&tId2);
    sleep(1);
    pthread_cancel(tId2);
    printf("Ho mandato la richiesta per la cancellazione del thread %ld\n",&tId2);
    sleep(5);
    printf("Ho terminato il programma\n");
    return 0;
}