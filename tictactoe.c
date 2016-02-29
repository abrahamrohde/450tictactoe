#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <time.h>
//#include "shmExample.h"
#define SHMSZ 27

void waitWhileEqual(char val, char* shm);
void makeMove(char turn, char* shm);
int checkBoard(char* shm);

 int main(int argc, char** argv)
 {
    printf("first\n");
    char c;
    int shmid;
    key_t key;
    char *shm, *s;
    printf("The mem address is:\n");

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key= 5678;

    /*
     * Create the segment.
     */
    if ((shmid= shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        return -1;
    }
    
    /*
     * Now we attach the segment to our data space.
     */
    if ((shm= shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return -1;
    }
    shm[0]= 'O'; // player 1
    shm[10]= 'N'; //no winner so far
    int i;
    for(i= 1; i < 10; i++)
    {
    shm[i]= 'E'; //empty space;
    }
   
    int pid= fork();
    
    if(pid != 0)
    {
    int winningBoard= 0;
    while(winningBoard== 0)
        {
            //parent
            //printf("parent\n");
            if(shm[0] == 'O')
            {
                //critical section
                printf("critical section\n");
                makeMove('O', shm);
                //printf("Made move\n");
                winningBoard= checkBoard(shm);
                shm[0] = 'T';
                //printf("checked board\n");
            }
            waitWhileEqual('T', shm);
        }
    if (shm[10]== 'O')
        {
            printf("Player one has won\n");
        }
        else
        {
            printf("Player two has won\n");
        }
    }
    else
    {
        
        int winningBoard= 0;
        while(winningBoard== 0)
        {
        if(shm[0]== 'T') //player 2
            {
                //critical section
                printf("child move\n");
                makeMove('T', shm);
                winningBoard= checkBoard(shm);
                shm[0] = 'O';
            }
            waitWhileEqual('O', shm);
        }
        return(0);
    }
    return 0;
 }
 
void waitWhileEqual(char val, char* shm)
{
    while(shm[0] == val && shm[10] == 'N')
    {
        //wait
    }
}
 
void makeMove(char turn, char* shm)
{
    int makingMove= 1;
    while(makingMove == 1)
    {
        //printf("makingMoveNow\n");
        //srand(time(NULL));
        int space = ((rand()%9) + 1);
        //printf("space: %i", space);
        printf("Space number: %i |Before move: %c\n", space, shm[space]);
        if (shm[space] == 'E')
        {
            shm[space] = turn;
            makingMove = 0;
        }
    }
    //printf("After move: %c\n", shm[space]);
    //printf("%c", shm[0]);
}
 
int checkBoard(char* shm)
{
    if (shm[1] == 'O' && shm[4] == 'O' && shm[7] == 'O')
    {
        shm[10]= 'O'; //winner has been found;
        return 1;
    }
    else if (shm[2] == 'O' && shm[5] == 'O' && shm[8] == 'O')
    {
        shm[10]= 'O'; //winner has been found;
        return 1;
    }
    else if (shm[3] == 'O' && shm[6] == 'O' && shm[9] == 'O')
    {
        shm[10]= 'O'; //winner has been found;
        return 1;
    }
    else if (shm[1] == 'O' && shm[2] == 'O' && shm[3] == 'O')
    {
        shm[10]= 'O'; //winner has been found;
        return 1;
    }
    else if (shm[4] == 'O' && shm[5] == 'O' && shm[6] == 'O')
    {
        shm[10]= 'O'; //winner has been found;
        return 1;
    }
    else if (shm[7] == 'O' && shm[8] == 'O' && shm[9] == 'O')
    {
        shm[10]= 'O'; //winner has been found;
        return 1;
    }
    else if (shm[1] == 'O' && shm[5] == 'O' && shm[9] == 'O')
    {
        shm[10]= 'O'; //winner has been found;
        return 1;
    }
    else if (shm[3] == 'O' && shm[5] == 'O' && shm[7] == 'O')
    {
        shm[10]= 'O'; //winner has been found;
        return 1;
    }
    else if (shm[1] == 'T' && shm[4] == 'T' && shm[7] == 'T')
    {
        shm[10]= 'T'; //winner has been found;
        return 1;
    }
    else if (shm[2] == 'T' && shm[5] == 'T' && shm[8] == 'T')
    {
        shm[10]= 'T'; //winner has been found;
        return 1;
    }
    else if (shm[3] == 'T' && shm[6] == 'T' && shm[9] == 'T')
    {
        shm[10]= 'T'; //winner has been found;
        return 1;
    }
    else if (shm[1] == 'T' && shm[2] == 'T' && shm[3] == 'T')
    {
        shm[10]= 'T'; //winner has been found;
        return 1;
    }
    else if (shm[4] == 'T' && shm[5] == 'T' && shm[6] == 'T')
    {
        shm[10]= 'T'; //winner has been found;
        return 1;
    }
    else if (shm[7] == 'T' && shm[8] == 'T' && shm[9] == 'T')
    {
        shm[10]= 'T'; //winner has been found;
        return 1;
    }
    else if (shm[1] == 'T' && shm[5] == 'T' && shm[9] == 'T')
    {
        shm[10]= 'T'; //winner has been found;
        return 1;
    }
    else if (shm[3] == 'T' && shm[5] == 'T' && shm[7] == 'T')
    {
        shm[10]= 'T'; //winner has been found;
        return 1;
    }
    else
    {
        return 0;
    }
}
