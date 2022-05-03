#include <stdio.h>

int main(){
    //loop fino a EOF aka (CTRL+D)
    int c,d;
    while ((c=getchar())!=EOF) {
        d=c;
        if(c>='a' && c<='z'){
            d=(d-'a')+'A';
        }
        if(c>='A' && c<='Z'){
            d=(d-'A')+'a';
        }
        putchar(d);
    }
    return 0;
}