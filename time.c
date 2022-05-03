#include <time.h>
#include<stdio.h>

void main(){
    time_t dataOdierna=time(NULL); //secondi dal 1/1/1970
    printf("Data odierna=%s",ctime(&dataOdierna));
}