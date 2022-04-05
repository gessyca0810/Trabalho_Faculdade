
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int x = 50;   /* uma variavel global compartilhada */
const clock_t MAXDELAY = 2000000;

void delay(clock_t ticks) { /* um atraso de ocupado */
  clock_t start = clock();
  do
    ; while (clock() < start + ticks);
}

void * adjustX(void *n)
{  int i = (int)n;
   while (1)   /* loop */
    {   printf("Ajuste = %2i; x = %i\n", i, x);
        x += i;
        delay(rand()%MAXDELAY);
   }
   return(n);
}

main()
{  int a;
   srand(time(NULL));
   pthread_t  up_thread, dn_thread;

   pthread_attr_t *attr;  /* variável atribuida a thread */
   attr=0;  

   printf("Criando threads:\n");
   pthread_create(&up_thread,attr, adjustX, (void *)1);
   pthread_create(&dn_thread,attr, adjustX, (void *)-1);

   while (1) /* loop  */
   { ;} 
}
