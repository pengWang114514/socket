/* CLIENT. Donner l'adresse IP et un pseudo en paramètre */
/* exemple "client 127.0.0.1 dr.ced", lancer en dernier. */

#include <stdio.h>             /* fichiers d'en-tête classiques */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#include <sys/socket.h>        /* fichiers d'en-tête "réseau" */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT_SERVEUR 5015      /* Numéro de port pour le serveur */
#define BUFFER_SIZE  1024      /* Taille maximum des messages */
#define MSG_SIZE 50	       /*Taille Maximum d'un message*/

int main(int argc, char *argv[]) {

	system("clear"); 
  /*Création des différentes chaine de caractères*/
	char question[100];
	memset(question, 0, (size_t) sizeof(question));
	strcpy(question, argv[2]);
  /*String contenant le début du message à envoyer au serveur*/
	strcat(argv[2], " : ");
  /*String contenant le texte à afficher avant de demander
  à saisir le message*/ 
	strcat(question, "> ");	

        char entree[MSG_SIZE];
        char reponse[MSG_SIZE];
	memset(reponse, 0, (size_t) sizeof(reponse));
  /* 1. On crée la socket du client. */
	int sclient = socket(AF_INET, SOCK_STREAM, 0);
  /* 2. On prépare l'adresse du serveur. */
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_SERVEUR);
	addr.sin_addr.s_addr = inet_addr(argv[1]);
  /* 3. On demande une connexion au serveur, tant qu'on y arrive pas. */
	int ok = connect(sclient, (struct sockaddr*) &addr, sizeof(addr));
	if(ok == -1) {perror("error connect()"); exit(1);}
  /* 4. On communique. */
	printf("Client de chat ouvert : \n");
	while(1){

		pid_t fils = fork();
		if(ok == -1) {perror("error fork()"); exit(1);}
		if(fils>0){

			int nbLus = read(sclient, reponse, sizeof(reponse));
			kill(fils, SIGKILL);
			if(nbLus<=0) break;
			printf("\n%s",reponse);
			memset(reponse, 0, (size_t) sizeof(reponse));
			continue;

		}
		else{

			while(1){

                        	write(0, question, sizeof(question));
				read(1, entree, sizeof(entree));
				int idxToDel = strlen(entree)-1; 
				memmove(&entree[idxToDel], &entree[idxToDel + 1], strlen(entree) - idxToDel);	
				char temp[MSG_SIZE];
				memset(temp, 0, (size_t) sizeof(temp));
			        strcpy(temp, argv[2]);
			   	strcat(temp, entree);
				write(sclient, temp, sizeof(temp));
			}

		}

	}

  /* 5. On termine et libère les ressources. */
	shutdown(sclient, SHUT_RDWR);
        close(sclient);

  return 0;
}
