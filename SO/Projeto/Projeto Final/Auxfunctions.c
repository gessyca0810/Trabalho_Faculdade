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


#define R 3
#define P 2

pthread_mutex_t sinal;

int MatrizRec[R]; //Recursos disponiveis
int MatrizUso[P][R]; //Recursos em uso
int MatrizNec[P][R]; //Recursos totais necessarios
int MatrizFal[P][R]; //Recursos solicitados

extern int i = 0; 
extern int j = 0;

int SeMaiorQueNec(int pID,int requisicao[])
{

     for (i = 0; i < R; ++i) // Verifica se a requisicao eh menor ou igual que a MatrizFal
     {
        if (requisicao[i] <= MatrizFal[pID][i])
        {  
            continue; 
        }
        else
        { 
            return -1; 
        }
     }
     return 0;
}

int SuficienteParaAlocar(int requisicao[])
{

     for (i = 0; i < R; ++i) // Verifica se a requisicao eh menor ou igual a MatrizRec
     {
          if (requisicao[i] <= MatrizRec[i])
          { 
               continue; 
          }
          else
          { 
               return -1; 
          }
     }
     return 0;
}

int modoseguro(int MatrizRec[R], int MatrizFal[P][R], int MatrizUso[P][R])
{
     int finish[P] = {0}; 
     int work[R];

     for(i = 0; i < R; i++)
     {
          work[i] = MatrizRec[i]; 
     }

     int k;
     for(i = 0; i < P; i++)
     {
          if (finish[i] == 0)
          {
               for(j = 0; j < R; j++)
               {
                    if(MatrizFal[i][j] <= work[j])  
                    {                                 
	                    if(j==R-1)
                         {
                              finish[i] = 1;

                              for (k = 0; k < R; ++k)
                              {
                                   work[k] += MatrizUso[i][k]; 

                              }
                                                                        
                              i = -1; 
                              break;
                         }
                         else
                         { 
                              continue; 
                         }
                    }

                    else
                    { 
                         break;
                    }
               }
          }
          else
          {  
               continue; 
          }
     }
           
     for(i = 0; i < P; i++)
     {

          if (finish[i] == 0)
          {              
               return -1;
          }

          else
          { 
               continue; 
          }

     }
            
     return 0;
}

int semreclib(int pID,int liberacao[])
{          
     for (i = 0; i < R; ++i) // Libera o recurso caso a o valor solicitado seja menor que o valor da MatrizUso
     {
          if (liberacao[i] <= MatrizUso[pID][i]) 
          { 
               continue; 
          }
          else
          { 
               return -1;
          }
     }
     return 0;
}

void Recdisp(int MatrizRec[R)  //PRINT
{
     for (i = 0; i < R; ++i)
     {
          printf("%d, ",MatrizRec[i]); //printa os recursos disponíveis
     }

     printf("\n");
     return;
}

void Usodisp(int MatrizUso[P][R) //PRINT
{
     for (i = 0; i < P; ++i)
     {
          printf("{ ");
          for (j = 0; j < R; ++j)
          {
               printf("%d, ", MatrizUso[i][j]); //printa a matriz dos recursos em uso
          }
     printf("}\n");
     }
     return;
}

void Faldisp(int MatrizFal[P][R]) //PRINT
{
    for (i = 0; i < P; ++i)
     {
          printf("{ ");
          for (j = 0; j < R; ++j)
          {
               printf("%d, ", MatrizFal[i][j]); //printa a matriz dos recursos em uso
          }
     printf("}\n");
     }
     return;
}

void reqlibdisp(int vec[]) // ====== DUVIDA ======//
{
     for (i = 0; i < R; ++i)
     {
          printf("%d, ",vec[i]);
     }
     printf("\n");
     return;
}
