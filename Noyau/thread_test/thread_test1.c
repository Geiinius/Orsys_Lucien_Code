#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
	int pid,i;
	pid=fork();
	switch(pid){
		case -1:
				printf("Erreur: echec du fork()\n");
				exit(1);
				break;
		case 0:	
				printf("Je suis le processus fils: PID-%d, mon père est : PPID-%d\n", getpid(), getppid());
				exit(0);
		default:
				printf("Je suis le père: le fils a un pid-%d\n",pid);
				wait(0);
				printf("Fin du père\n");

	}


}
