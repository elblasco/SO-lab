#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(){
    int fid=fork(),wid,st,r;
    srand(time(NULL));
    r=rand()%256;
    if(fid==0){
        printf("Sono il figlio.....(%d)\n",r);
        fflush(stdout);
        sleep(3);
        printf("Fatto!!!\n");
        exit(r);
    }
    else{
        printf("Padre.....\nDevo aspettare mio figlio\n");
        wid=wait(&st);
        printf("....l'id del figlio è: %d==%d (st=%d)\n",fid,wid,WEXITSTATUS(st));
    }
    return 0;
}