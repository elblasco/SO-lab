#include <signal.h>

int main(){
    signal(SIGTSTP,SIG_IGN);
    while(1);
}