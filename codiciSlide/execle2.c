#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv){
    printf("Questo e execle2.c con par: %s e %s, ha anche CIAO= %s\n",argv[0],argv[1],getenv("CIAO"));
}