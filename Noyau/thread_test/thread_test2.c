#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *fonction_de_thread(void *arg);
char message []= "Hello Wolrd";

int main(void)
{
	int res;
	pthread_t un_thread;
	void *resulat_de_thread;
	res=pthread_create(&un_thread, NULL, fonction_de_thread, (void*)message);

	if(res!=0){

		perror("Ehec de la création du thread");
		exit(EXIT_FAILURE);
	}

	printf("En attente de terminasion du thread....\n");

	res=pthread_join(un_thread,&resulat_de_thread);

	if(res!=0){

		perror("Echec de l'ajout de thread");
		exit(EXIT_FAILURE);
	}


	printf("Retour du thread, il a renvoyé: %s\n", (char *)resulat_de_thread);
	printf("Voici a présent le message: %s\n", message);
	exit(EXIT_SUCCESS);


}

void *fonction_de_thread(void *arg){
	printf("La fonction_de_thread est en cours d'exécution. L'argument était: %s\n", (char *) arg);
	sleep(3);
	strcpy(message,"Salut !");
	pthread_exit("Merci pour le temps processeur");
}
