#include <stdio.h>
#include <pthread.h>

void *OLA(void *argumentos) 
{
    printf("\nOLÁ MUNDO.. BEM VINDO :-)\n\n");
}

int main ( )
{
    pthread_t thread;
    int flag, i;
    printf("criar uma thread\n");
    flag = pthread_create(&thread, NULL, OLA, NULL);
    if (flag!=0)
        printf("Erro na criação da thread\n");
    pthread_exit(NULL);
    return 0;
}
