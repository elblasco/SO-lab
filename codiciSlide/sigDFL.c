#include <signal.h>
int main(){
    signal(SIGTSTP,SIG_DFL);
    while(1);
}