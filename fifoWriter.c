#include <bits/types/sigset_t.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/*extern int errno;

int main(int argc,char **argv){
    int fd;
    char *pathFifo="/tmp/fifo1";
    char str1[80], *str2="Sono il programma scrittore";
    int ret = mkfifo(pathFifo,S_IRUSR|S_IWUSR); //Crea una pipe se non esiste
    if(ret==-1){
        fprintf(stderr,"errno=%d\n",errno);
        fprintf(stderr,"Sterror: %s\n",strerror(errno));
    }
    printf("Ho creato la pipe fifo %d\n", ret);
    fd=open(pathFifo,O_WRONLY|O_NONBLOCK); //Apre il file di fifo in sola scrittura
    if(fd!=0){
        fprintf(stderr,"errno=%d\n",errno);
        fprintf(stderr,"Sterror: %s\n",strerror(errno));
    }
    printf("Ho aperto in scrittura la pipe FIFO ");
    write(fd,str2,strlen(str2)+1); //write nel file e poi lo chiude
    printf("Ho scritto nella pipe fifo\n");
    close(fd);
    fd=open(pathFifo,O_RDONLY);
    printf("Sto per leggeee dalla pipe FIFO\n");
    read(fd,str1,sizeof(str1));
    printf("Ho letto dalla pipe FIFO\n");
    printf("Ho letto dal file %s\n",str1);
    close(fd);
}*/

int main (int argc, char *argv[]) {
int fd; char * fifoName = "/tmp/fifo1";
char str1[80], * str2 = "I'm a writer";
mkfifo(fifoName,S_IRUSR|S_IWUSR); //Create pipe if it doesn’t exist
fd = open(fifoName, O_WRONLY); // Open FIFO for write only
write(fd, str2, strlen(str2)+1); // write and close
close(fd);
fd = open(fifoName, O_RDONLY); // Open FIFO for Read only
read(fd, str1, sizeof(str1)); // Read from FIFO
printf("Reader is writing: %s\n", str1);
close(fd);
}