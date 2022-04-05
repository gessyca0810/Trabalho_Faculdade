#include <stdio.h>
#include <stdlib.h>

const clock_t MAXDELAY = 2000000;
int x = 50;   /* variável global */

void delay(clock_t ticks) { /* um atraso de ocupado */
  clock_t start = clock();
  do
    ; while (clock() < start + ticks);
}

void adjustX(char * legend, int i) {
   while (1)  /* loop */
   {   printf("%s: %i\n", legend, x);
       x += i;
       delay(rand()%MAXDELAY);
   }
}

main()
{  int c;
   srand(time(NULL));
   printf("Criando um novo processo:\n");
   c = fork();
   printf("Processo %i criado\n", c);
   if (c==0) 
      adjustX("filho", 1);   
   else
      adjustX("pai", -1);  
}
