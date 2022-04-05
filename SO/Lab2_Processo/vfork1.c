#include <stdio.h>
#include <stdlib.h>

int globvar = 6;

int main(void) {
 pid_t pid;
 
 printf("Eu fui criado pelo processo %d\n",getppid());
 printf("Eu sou o pai %d e eu vou criar um filho\n",getpid());
 printf("Antes de usar o vfork\n");

  if ((pid = vfork()) < 0) 
  {
   printf("vfork error");
  } 
  else if (pid == 0) 
  {
   printf("Eu sou o processo filho %d\n\n",getpid());
   globvar++;
   exit(0);
  }
  printf("PID Pai = %ld, Variavel Global = %d\n\n\n", (long)getpid(), globvar);
  return 0;
}
