/*Integrantes
Carlos Eduardo Cardia Fernandez - 11911EMT016
Gessyca Carneiro Bernandes - 11911EMT022
Laura Bueno Ferreira - 11911EMT017
Talles Martins de Carvalho - 11911EMT014
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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

int obterRec(int pID,int requisicao[])
{
     if (SeMaiorQueNec(pID,requisicao) == -1) // Verifica se o numero de recursos solicitados nao eh maior que o necessario para o processo.
     {
          printf("Numero de recursos solicitados eh maior do que o necessario para o processo.\n");
          return -1;
     }
     printf("Os recursos estao sendo alocados.\n");

     if(SuficienteParaAlocar(requisicao) == -1) // Verifica se o banqueiro tem recursos suficientes para fornecer ao processo.
     {
          printf("Nao ha recursos suficientes.\n");
          return -1;
     }

        
     for (i = 0; i < R; ++i)  // Faz as devidas modificacoes de acordo com as requisicoes
     {
          MatrizFal[pID][i] -= requisicao[i]; 
          MatrizUso[pID][i] += requisicao[i];
          MatrizRec[i] -= requisicao[i]; 
     }

     printf("Verificando se o estado e seguro\n");

     // Verifica se esta no modo seguro

     if (modoseguro(MatrizRec[R], MatrizFal[P][R], MatrizUso[P][R]) == 0) 
     {
          printf("\nx========================x\n|Esta Seguro. Todos recursos estao alocados|\nx=========================x\n");
                        
          exit(1);
          return 0;
     }
     else
     {           
          printf("\nx=====================x\n|Estado nao esta seguro.          |\nx=====================x\n");
          exit(1);
              
          return -1;
     }
}

int liberaRec(int pID,int liberacao[]) // Libera os recursos
{          

     if(semreclib(pID,liberacao) == -1) // Verifica se ha recursos no processo para ser liberado
     {
          printf("Not enought Resources.\n");
          return -1;
     }
     for(i = 0; i < R; i++) // Faz as devidas modificacoes de acordo com os recursos liberados
     {
          MatrizUso[pID][i] -= liberacao[i];
          MatrizFal[pID][i] += liberacao[i];
          MatrizRec[i] += liberacao[i];
     }
     printf("Released.\nMetrix Available:\n");
     Recdisp(MatrizRec[R]);
     printf("Metrix Allocated:\n");
     Usodisp(MatrizUso[P][R]);
     printf("Metrix Need:\n");
     Faldisp(MatrizFal[P][R]);
     return 0;
}