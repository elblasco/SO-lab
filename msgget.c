#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main(){
    key_t chiaveCoda=56;
    int idCoda=msgget(chiaveCoda,0777|IPC_CREAT|IPC_EXCL);
    printf("L'identificativo della coda è: %d\n",idCoda);
    return 0;
}