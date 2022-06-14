#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    int i=23;
    int figlio=fork();
    if(figlio==0){
        ++i;
        printf("Per il figlio i vale %d\n",i);
    }
    else{
        while(wait(NULL )>0);
        printf("Attualmente la i vale %d\n",i);
    }
    return 0;
}
/*
 * Le variabili vengono copiate ma quando un figlio/padre ne modifica il valore
 * la modifica è relativa al namespace del proceso che modifica il valore
 * in questo caso i parte da 23 ma il figlio la modifica a 24, quindi per lui è 24.
 * Il padre aspetta i figli, ma per lui i vale ancora 23.
*/