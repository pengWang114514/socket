#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/wait.h>
#define TABSIZE 10000

int main() {
		const int TABSIZE
    unsigned char arr[TABSIZE];
    srandom(time(NULL));
    
    for (int i = 0; i < TABSIZE; i++)
        arr[i] = (unsigned char) (random() % 255) + 1;
    
   
    printf("Entrer un nombre entre 0 and %d: ", TABSIZE);
    scanf(" %d", &i);
    if (i >= 0 && i < TABSIZE) arr[i] = 0;
    
    int moitie = TABSIZE*0.5;
    int i = 0;
    bool trouve = false;
    int status = 0;
    pid_t id = fork();
    if(id == 0)
    {
        while (!trouve && i <= moitie)
        {
            if(arr[i] == 0)
            {
                trouve = true;
            }
            i++;
        }  
        exit(trouve);
    }
    wait(&status);
    int res = WEXITSTATUS(status);
    if(res == 1)
    {
        printf("Il y a un 0\n");
        exit(0);
    }
    else
    {
        i = moitie + 1; 
        while (!trouve && i <= TABSIZE)
        {
            if(arr[i] == 0)
            {
                trouve = true;
            }
            i++;
        }  
        if(trouve)
        {
            printf("il y a un 0\n");
        }
        else
        {
            printf("Il n'y a pas de 0\n");
        }
    }
    
    return 0;
}
