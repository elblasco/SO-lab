#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *funzione(void * parametro){
    printf("Il thread %ld ha iniziato\n",*(pthread_t *)parametro);
    sleep(3);
    char * str="Stringa di ritorno";
    pthread_exit((void *)str); //Poteri anche scrivere return (void *) str;
}

int main(){
    pthread_t tId;
    void * retrunFromTheThread; //Deve essere per forza un punatatore a void
    pthread_create(&tId,NULL,funzione,(void *)&tId);
    pthread_join(tId,&retrunFromTheThread); //Aspetta il thread
    //Ora è imperativo fare il casting del valore di ritorno
    printf("Il thread %ld ha ritornato %s\n",tId,(char *)retrunFromTheThread);
}