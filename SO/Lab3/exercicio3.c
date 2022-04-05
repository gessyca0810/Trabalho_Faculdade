#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 10

void *imprime(void *argumentos)
{
    int valor =* (int *) argumentos;
    printf("Valor: %d \t", valor );
}

int main ()
{
    pthread_t threads[NUM_THREADS];
    int i;
    
    for(i=0;i < NUM_THREADS;i++)
        pthread_create(&threads[i], NULL, imprime, &i);  

    printf("Espera a finalização das threads criadas \n");  
    
    for(i=0; i < NUM_THREADS;i++)
        pthread_join(threads[i],NULL);  
    return 0;
 }
