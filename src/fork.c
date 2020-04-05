/**
 * - amélioration espéré: faire marcher le programme pour 1,2,4,8,16,3,-1
 * - amélioration effective:
 * - temps d'exécution pour 77777:
 *
 *
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#define MAX 10000000

long int memory = 0;
//int valfin = 2147483647;

int conject(long int val, int etape, long int *tab)
{
    if (val % 2 == 0)
        tab[val][1] = val / 2;
    else
        tab[val][1] = 3 * val + 1;

    memory++;

    tab[val][0] = etape;

    memory++;

    printf("%ld. %ld\n", tab[val][0], val);
    if (val == 1)
        return 1;

    int status;

    if (fork() == 0)
    {
        conject(tab[val][1], etape + 1);
    }
    else
    {
        wait(&status);
        exit(status);
    }
}

int main(int argc, char *argv[])
{
    //Création IPC//
    long int (*tab)[3];
    key_t key;
    key = ftok("/tmp", 'A');
    if(key == -1){perror("ftok"); exit(EXIT_FAILURE);};
    int id = shmget(key, 3*MAX, IPC_CREAT | IPC_EXCL | 0666);

    if(id == 1){
        switch(errno){
            case EEXIST:
                fprintf(stderr,"Existe déjà !\n");
                break;
            default:
                perror("shmget");
                break;
        }
        exit(EXIT_FAILURE);
    }
    tab=(long int (*)[3])shmat (id, NULL, SHM_R | SHM_W);
    if(tab==NULL){perror("shmat"); exit(EXIT_FAILURE);}

    //Traitement//
    long int valdebut = atoi(argv[1]);

    if (valdebut > 0 && argc > 1)
    {
        conject(valdebut, 1, tab);
    }
    printf("\nCases mémoire utilisées %ld\n", memory);

    return 0;
}
