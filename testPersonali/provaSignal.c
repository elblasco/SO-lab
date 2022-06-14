#include<stdio.h>
#define _NSIG		64
#define _NSIG_BPW	64
#define _NSIG_WORDS	(_NSIG / _NSIG_BPW)

int main(){
    printf("%d\n",_NSIG_WORDS);
    return 0;
}