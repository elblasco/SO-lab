#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

struct book{
    char title[15];
    unsigned short chapters;
}book1,book2;

struct msg_buffer{
    long mtype;
    struct book mtext;
}message1,message2;

int main(){

    strcpy(book1.title,"Transformers");
    strcpy(book2.title,"Bella ciao");
    book1.chapters=12;        
    book2.chapters=10;
    message1.mtext=book1;
    message2.mtext=book2;
    message1.mtype=1;
    message2.mtype=2;

    key_t key=20;
    int id=msgget(key,0777|IPC_CREAT);

    int figlio=fork();
    if(figlio==0){
        struct msg_buffer buffer;
        msgrcv(id,&buffer,sizeof(message2),2,0);
        printf("Il figlio ha ricevuto il libro %s con %d capitoli\n",buffer.mtext.title,buffer.mtext.chapters);
    }
    else{
        msgsnd(id,&message1,sizeof(message1),0);
        msgsnd(id,&message2,sizeof(message2),0);
        while(wait(NULL)>0);
        int esito=msgctl(id,IPC_RMID,NULL);
        system("ipcs");
        printf("Padre %d e figlio %d hanno finito, coda rimossa con esito %d\n",getpid(),figlio,esito);
    }
    return 0;
}