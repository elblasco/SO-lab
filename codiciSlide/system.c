#include <stdlib.h>
#include <stdio.h>

void main(){
    int risultato=system("echo buongiorno prof");
    printf("%d\n",risultato);
    risultato=system("if [[ $PWD < /LAB/ ]]; then echo esiste /LAB/; else echo non esiste /LAB/; fi");
    printf("%d\n",risultato);
}