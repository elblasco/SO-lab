#include<stdio.h>
#define MAX 256

char* stringrev(char* str){
    int index=0;
    for(;str[index]!='\0';++index);
    for(int i=0;i<(index/2);i++){
        char buffer=str[i];
        str[i]=str[index-i-1];
        str[index-i-1]=buffer;
    }
    return str;
}

int stringpos(char * str,char chr){
    int found=0;
    int i=0;
    for(;found==0 && str[i]!='\0';i++){
        (str[i]==chr)?found++:found;
    }
    return i;
}

int main(){
    char str[MAX];
    scanf("%s",str);
    char *rev=stringrev(str);
    printf("La stringa stampata è %s\n",rev);
    printf("Il carattere 3 è in posizione: %i\n",stringpos(rev,'3'));
    return 0;
}