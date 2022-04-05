/*Integrantes
Carlos Eduardo Cardia Fernandez - 11911EMT016
Gessyca Carneiro Bernandes - 11911EMT022
Laura Bueno Ferreira - 11911EMT017
Talles Martins de Carvalho - 11911EMT014
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "Processos.h"
#include "Banqueiro.h"
#include "Auxfunctions.h"
#include "Sistema.h"

#define R 3
#define P 2

pthread_mutex_t sinal;

int MatrizRec[R]; //Recursos disponiveis
int MatrizUso[P][R]; //Recursos em uso
int MatrizNec[P][R]; //Recursos totais necessarios
int MatrizFal[P][R]; //Recursos solicitados


int i = 0; 
int j = 0;


int main()
{

     for(i=0; i < R; ++i)
     {
          scanf("%d",&MatrizRec[i]);

     }
     printf("Recursos em uso\n"); // o que o recurso está usando
     for(i = 0; i < P; i++)
     {        
          for(j = 0; j< R; j++)
          {       
               scanf("%d",&MatrizUso[i][j]);        
          }
     }

     printf("Recursos necessarios\n"); // o que o recurso realmente quer
     for(i = 0; i < P; i++)
     {               
          for(j = 0; j< R; j++)
          {      
          scanf("%d",&MatrizNec[i][j]);  
          }
          }
               
     for (i = 0; i < P; ++i)
     {
          for (j = 0; j < R; ++j)
          {
               MatrizFal[i][j] = MatrizNec[i][j] - MatrizUso[i][j];
          }
     }

     Recdisp(MatrizRec);
     Usodisp(MatrizUso);
     Faldisp(MatrizFal);
     ThreadCreate();

     return 0;
}


int ThreadCreate()
{
    pthread_mutex_init(&sinal,NULL); // Inicia o semaforo
    pthread_attr_t threads; // Define a thread
    pthread_attr_init(&threads); // Inicia a thread
    pthread_t *tid = malloc(sizeof(pthread_t) * P); // Cria o ID da thread

    int *pid = malloc(sizeof(int) * P); // Cria o ID do processo

    for(i = 0; i < P; i++) // Cria as threads 
    {
        *(pid + i) = i; // ================ duvida ====================
        pthread_create((tid+i), &threads, processos, (pid+i));
    }

    for(i = 0; i < P; i++) // Finaliza as threads
    {
        pthread_join(*(tid+i),NULL);
    }
    return 0;

}
