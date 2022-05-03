#include <unistd.h>
#include <stdio.h>

int main(){
    char *argomenti[]={"par1","par2",NULL};
    execv("./execv2.out",argomenti);
    printf("Questo e execv1\n");
    return 0;
}