#include<stdio.h>
#include<errno.h>
#include<string.h>

extern int errno; //Dichiarazione di una variabile esterna e globale

int main(){
   FILE * pf;
   pf=fopen("FileCheNonEsiste.bf","rb");
   if(pf==NULL){ //Se il file non esiste
       fprintf(stderr,"Errore numero=%d\n",errno);
       perror("Errore stampato da perror");
       fprintf(stderr,"Strerror: %s\n",strerror(errno));
   }
   else{
       fprintf(stdout,"Andato tutto bene\n");
       fclose(pf);
   }
}