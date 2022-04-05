#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

//Execute esse codigo e analise o resultado. O processo Pai foi finalizado? O que aconteceu? 

int main(){
sleep(1);
 int pid ;
   printf("Eu sou o pai %d e eu vou criar um filho \n",getpid()) ;
   pid=fork() ; /* criacao do filho */
   if(pid==-1) /* erro */
   {
      perror("impossivel de criar um filho\n") ;
   }    
   else if(pid==0) /* acoes do filho */
   {
      printf("\tOi, eu sou o processo %d, o filho. Meu pai é %d\n",getpid(), getppid()) ;
      printf("\tO dia esta otimo hoje, nao acha?\n") ;
      printf("\tBom, desse jeito vou acabar me instalando para sempre\n");
      printf("\tOu melhor, assim espero!\n") ;
      
      for(;;); 
   }
   else /* acoes do pai */
   {
       wait(NULL);  
       printf("As luzes comecaram a se apagar para mim, %d\n",getpid()) ;
       printf("Minha hora chegou : adeus, %d, meu filho\n",pid) ;
       /* e o pai morre de causas naturais */ 
    }
    return 0;
}
