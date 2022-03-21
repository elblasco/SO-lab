#include<stdio.h>
/**
 * @brief The main of the program, print the lenght of the first argument
 * 
 * @param argc  Numbere of arguments 
 * @param argv  Matrix of arguments
 * @return int 
 */
int main(int argc,char ** argv){
    int size=0;
    for (int i = 0; argv[1][i]!='\0'; i++){
        ++size;
    }
    printf("%i\n",size);
    return 0;
}