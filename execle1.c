#include <unistd.h>
#include <stdio.h>

int main(){
    char *envVar[]={"CIAO=viva sistemi operativi",NULL};
    execle("./execle2.out","par1","par2",NULL,envVar);
    printf("Questo e execle1.c\n");
    return 0;
}