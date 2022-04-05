/*Integrantes
Carlos Eduardo Cardia Fernandez - 11911EMT016
Gessyca Carneiro Bernandes - 11911EMT022
Laura Bueno Ferreira - 11911EMT017
Talles Martins de Carvalho - 11911EMT014
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "Auxfunctions.h"
#include "Banqueiro.h"
#include "Processos.h"
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

void *processos(void* processosID) // Faz a chamada de requisicao e liberacao dos recursos para os processos
{     
     int pID = *(int*)processosID; //============DUVIDA===========//;-; :c
     int c=0;

     while(c<3)
     {
        sleep(1);
        int requisicao[R]; // Matriz de requisicao de recursos
	    pthread_mutex_lock(&sinal); // Trava o programa para apenas fazer requisicao, garantindo a sincronizacao

        for(i = 0; i < R; i++) // Realiza uma requisicao aleatoria de recursos
        {
            if(MatrizFal[pID][i] != 0)
            {
                requisicao[i] = rand() % MatrizFal[pID][i];              
            }
               
            else
            {
                requisicao[i] = 0;
            }
        }

        reqlibdisp(requisicao); // Printa o que foi solicitado

        obterRec(pID,requisicao); // Obtem os recursos solicitados

        pthread_mutex_unlock(&sinal); // Libera o sinal
        
        //random release vector gernerate karne ke liye            
        sleep(1);

        int liberacao[R]; // Matriz de liberacao de recursos
        pthread_mutex_lock(&sinal); // Trava o programa para nao requerir recursos enquanto esta sendo feito a liberacao

        for(i = 0; i < R; i++) // Realiza uma liberacao aleatoria de recursos
        {
            if(MatrizUso[pID][i] != 0)
            {
                liberacao[i] = rand() % MatrizUso[pID][i]; 
            }

            else
            {
                liberacao[i] = 0;
            }
        }
      
        reqlibdisp(liberacao); // Printa o que foi liberado
        liberaRec(pID,liberacao); //Libera os recursos solicitados
        pthread_mutex_unlock(&sinal); // Libera o sinal

        c++;
    }
} 