**Il genio del prof ha caricato alcune soluzioni in forma testuale e non in pdf.**  
**Le soluzioni sono qua sotto triportate.**  
# Esercizi su makefile  
    # Creare un makefile con:
    # - una regola "help" di default che mostri una nota informativa,
    # - una regola "backup" che crei un backup di una cartella appendendo “.bak” al nome,
    # - una regola "restore" che ripristini il contenuto originale.
    # Per definire la cartella sorgente passarne il nome come variabile,
    # ad esempio:
    #   make -f mf-backup FOLDER=...
    #   (la variabile FOLDER è disponibile dentro il makefile)
    #
    # In queesta versione il "backup" di una cartella avviene
    # copiando l'intera cartella in un'altra con ".bak" aggiunto al nome,
    # mentre il "restore" avviene rinominando la versione ".bak" e quindi
    # eliminando il backup stesso, sempre che non esista già l'originale.
    # Si può espandere l'esempio per aggiungere maggiori controlli e opzioni.

    # .SILENT dichiara le regole di cui NON fare l'echo
    # evitando di usare "@" prima di ogni comando
    .SILENT: help backup restore

    # .PHONY dichiara le pseudo-regole (con target non file
    # o comunque con target da non verificare)
    .PHONY: help backup restore

    # per comodità si definiscono alcune variabili
    NAME=mf-backup
    APP=make -f $(NAME)

    # regola "help" di default
    help:
      echo
      echo backup/restore folder
      echo "  $(APP) backup  FOLDER=..."  # backup folder (create .bak)
      echo "  $(APP) restore FOLDER=..." # restore folder (retrieve from .bak)
      echo

    # regola "backup":
    # verifica esista la cartella sorgente e crea una copia con ".bak"
    backup:
      echo "Backup folder '$(FOLDER)'"
      [ -d "$(FOLDER)" ] && cp -rp "$(FOLDER)" "$(FOLDER).bak" || echo "?Error"

    # regola "restore":
    # verifica esista la versione ".bak" e non ci sia l'orginiale e ripristina il contenuto
    restore:
      echo "Restore folder '$(FOLDER)'"
      [ -d "$(FOLDER).bak" ] && [ ! -d "$(FOLDER)" ] && mv "$(FOLDER).bak" "$(FOLDER)" || echo "?Error"  
# Esercizio pipe Labso2022-Lesson_07 slide 20  
    /*
    Processo P1 invia un intero casuale nell'intervallo 0..5 a P2
    Processo P2 invia una lettera casuale nell'intervallo A..F a P1
    ciclando fino a generare 0 da parte di P1 o A da parte di P2

    Evoluzioni:
    - aggiungere tutti i controlli sugli errori
    - vincolare strettamente il termine delle azioni alla ricezione di uno dei due messaggi di stop 
    */
    #include <stdio.h>
    #include <time.h>
    #include <stdlib.>
    #include <string.h>

    #define READ  0
    #define WRITE 1

    int rnd() {
        srand(time(NULL)+getpid());
        return rand()%6;
    }

    int main() {
        char buffer[10], dat[2], p;
        int p1p2[2], p2p1[2], r=rnd(), l=0;
        pipe(p1p2); pipe(p2p1);
        if (fork()>0) {
            p=1; printf("[P%d]\n", p); fflush(stdout);
            close(p1p2[READ]); close(p2p1[WRITE]);
        } else {
            p=2; printf("[P%d]\n", p); fflush(stdout);
            close(p1p2[WRITE]); close(p2p1[READ]);
        };
        while (r>0) {
            l++;
            if (p==1) {
                sprintf(buffer, "%d", r);
                printf("[P%d](%d) -> %d\n", p, l, r); fflush(stdout);
            } else {
                sprintf(buffer, "%c", r+65);
                printf("[P%d](%d) -> %c\n", p, l, r+65); fflush(stdout);
            };
            buffer[1]='\0';
            if (p==1) {
                write(p1p2[WRITE], buffer, strlen(buffer)+1);
                read( p2p1[READ],  dat, 3);
            } else {
                read( p1p2[READ],  dat, 3);
                write(p2p1[WRITE], buffer, strlen(buffer)+1);
            };
            printf("[P%d](%d) <- %s\n", p, l, dat); fflush(stdout);
            r=rnd();
        };
        if (p==1) {
            printf("[P%d](%d) %d STOP!\n", p, l, r);
        } else {
            printf("[P%d](%d) %c STOP!\n", p, l, r+65);
        };
        fflush(stdout);
        return 0;
    }
