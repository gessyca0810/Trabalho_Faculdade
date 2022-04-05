#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  
   pid_t pid;

	printf("Eu fui criado pelo processo %d\n",getppid());
        printf("Eu sou o pai %d e eu vou criar um filho\n",getpid());

	pid = fork(); /* criacao do filho */

	if (pid < 0) {  /* erro */
		fprintf(stderr, "Impossível criar o filho!!!\n");
		return 0;
	}
	else if (pid == 0) {  /* acoes do filho */
		printf("Eu sou o processo filho %d e vou executar o comando ls\n\n",pid);
		execlp("/bin/ls","ls",NULL);

	}
	else {  /*Processo Pai */
		/* o processo pai espera o filho completar pelo comando wait*/
                wait(NULL);        
		printf("\nProcesso Filho Completo\n");
                    
		return 0;
	}
}
