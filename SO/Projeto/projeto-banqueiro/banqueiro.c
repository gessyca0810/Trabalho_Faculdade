/*Integrantes
Carlos Eduardo Cardia Fernandez - 11911EMT016
Gessyca Carneiro Bernandes - 11911EMT022
Laura Bueno Ferreira - 11911EMT017
Talles Martins de Carvalho - 11911EMT014
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <strings.h>

#include "processos.h"
#include "sistema.h"

int R; //Quantidade de tipos de recursos 
int P; //Quantidade de processos

pthread_mutex_t sinal;
int *MatrizRec; //Recursos disponiveis 
int **MatrizUso; //Recursos em uso
int **MatrizNec; //Recursos totais necessarios
int **MatrizFal; //Recursos solicitados
int i = 0; 
int j = 0;

int liberaRec(int pID,int liberacao[]) // Libera os recursos
{          

     if(semreclib(pID,liberacao) == -1) // Verifica se ha recursos no processo para ser liberado
     {
          printf("Not enought Resources.\n");
          return -1;
     }
     for (int i = 0; i < R; i++) // Faz as devidas modificacoes de acordo com os recursos liberados
     {
          MatrizUso[pID][i] -= liberacao[i];
          MatrizFal[pID][i] += liberacao[i];
          MatrizRec[i] += liberacao[i];
     }
     printf("Released.\nMetrix Available:\n");
     Recdisp();
     printf("Metrix Allocated:\n");
     Usodisp();
     printf("Metrix Need:\n");
     Faldisp();
     return 0;
}

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

     if (modoseguro() == 0) 
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

int main(int argc, char *argv[]) 
{
     printf("Algoritmo do banqueiro \n");

     R = argc - 4; // Quantidade de recursos
     MatrizRec = malloc(R * sizeof(int)); // Guarda os espaços para a matriz de recursos disponíveis

     for (int i = 0; i < argc; i++)
     {
          if(!strcmp(argv[i], "-n")) // Identifica onde está a quantidade de processos
          {
               P = atoi(argv[i+1]);
          }
          if(!strcmp(argv[i], "-a")) // Identifica a quantidade de recursos de cada processo
          {
               for(int j = 1; j < R + 1; j++)
               {
                    if (!strcmp(argv[i + j],"-n") || !atoi(argv[i+j])) // Ve se o próximo é o -n
                    {
                         break;
                    }
                    MatrizRec[j - 1] = atoi(argv[i+j]);  // Salva os valores na matriz de recursos
               }
          }
     }
     
     
    printf("Quantos recursos estao disponiveis no banco:\n");
    //Printa a quantidade de recursos que o banqueiro tem
    for(i=0; i < R; ++i) 
    {
        printf("%d ",MatrizRec[i]);    
    }
    
    printf("\n");


    
    MatrizUso = (int**)malloc(P * sizeof(int**));
   
    for(i = 0; i < P; i ++){
        MatrizUso[i] = (int*)malloc(R * sizeof(int));
    }

    printf("Recursos em uso:\n"); 
    //Printa quantos recursos cada processo esta utilizando

    for(i = 0; i < P; i++) 
    {        
        for(j = 0; j< R; j++)
        {   
            MatrizUso[i][j] = 0;    
            printf("%d ",MatrizUso[i][j]);        
        }
        printf("\n");
    }
    

    MatrizNec = (int**)malloc(P * sizeof(int**));
    for(int i = 0; i < P; i ++){
        MatrizNec[i] = (int*)malloc(R * sizeof(int));
    }
    
    printf("Recursos que os processos necessitam:\n");
    //Printa quantos recursos cada processo precisa
    
    for(i = 0; i < P; i++) 
    {        
        for(j = 0; j< R; j++)
        {   
            MatrizNec[i][j] = rand() % MatrizRec[j] + 1;    
            printf("%d ",MatrizNec[i][j]);        
        }
        printf("\n");
    }

    MatrizFal = (int**)malloc(P * sizeof(int**));
    for(int i = 0; i < P; i ++){
        MatrizFal[i] = (int*)malloc(R * sizeof(int));
    }
            
    
    // Calcula quantos recursos falta para cada processo 
    for (int i = 0; i < P; ++i) 
    {
        for (int j = 0; j < R; ++j)
        {
            MatrizFal[i][j] = MatrizNec[i][j] - MatrizUso[i][j];
        }
    }

    pthread_mutex_init(&sinal,NULL); // Inicia o semaforo
    pthread_attr_t threads; // Define a thread
    pthread_attr_init(&threads); // Inicia a thread
    pthread_t *tid = malloc(sizeof(pthread_t) * P); // Cria o ID da thread

    int *pid = malloc(sizeof(int) * P); // Cria o ID do processo

    for(i = 0; i < P; i++) // Cria as threads 
    {
        *(pid + i) = i;
        pthread_create((tid+i), &threads, processos, (pid+i));
    }

    for(i = 0; i < P; i++) // Finaliza as threads
    {
        pthread_join(*(tid+i),NULL);
    }
    return 0;

}