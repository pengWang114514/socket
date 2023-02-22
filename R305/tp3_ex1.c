#define SIZE 20
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int tab[SIZE];
void * bulle(void * arg){
    int tmp,pas_trie=1;
    while(pas_trie){
        pas_trie=0; //si c'est bien trie
        for(int i = 0;i<SIZE;i++){
            if(tab[i]>tab[i+1]){
	            tmp=tab[i];
	            tab[i]=tab[i+1];
	            tab[i+1]=tmp;
	            pas_trie=1;// le 1 veut dire si pas dans bon ordre il affiche 1
	        }
        }
    }
    return NULL;
}
void * plomb(void * arg) { 
        int tmp, pas_trie=1;
        while (pas_trie){
        pas_trie=0;
            for(int i=SIZE-1;i>0;i--){
                if(tab[i]<tab[i-1]){
                    tmp=tab[i];
                    tab[i]=tab[i-1];
                    tab[i-1]=tmp;
                    pas_trie=1;
                }
            }
        } 
        return NULL;   
 }
void shuffle() {
int i, j, temp;
for (i = SIZE-1; i > 0; i-- ) {
j = random() % (i + 1);
temp = tab[i];
tab[i] = tab[j];
tab[j] = temp;
}
}
int main() {
    int i;
    pthread_t bulle_id, plomb_id;
    srandom(time(NULL));
    for (i = 0; i < SIZE; i++) tab[i] = i + 1;
    for (i = 0; i < 3000; i++) {
    shuffle();
    if (pthread_create(&bulle_id, NULL, bulle, NULL) != 0) exit(1);
    if (pthread_create(&plomb_id, NULL, plomb, NULL) != 0) exit(1);
    pthread_join(bulle_id, NULL);
    pthread_join(plomb_id, NULL);
}
for (i = 0; i < SIZE; i++) printf("%d ", tab[i]);
putchar('\n');
return 0;
}
