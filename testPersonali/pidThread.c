#include<pthread.h>
#include<unistd.h>
#include<stdio.h>

void *ottieni_pid(){
    printf("Sono il thread e ho PID: %d\n",getpid());
}

int main(){
    pthread_t t_id;
    pthread_create(&t_id,NULL,ottieni_pid,NULL);
    printf("Io invece sono il padre con PID: %d\n",getpid());
    printf("Il thread generato ha id: %u\n",t_id);
    sleep(3);
    return 0;
}

/*
 *In Linux il processo e il thread da lui generato hanno lo stesso PID
*/