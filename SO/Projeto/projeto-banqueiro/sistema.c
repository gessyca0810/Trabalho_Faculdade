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

#include "banqueiro.h"
#include "processos.h"

extern int R; //Quantidade de tipos de recursos 
extern int P; //Quantidade de processos

extern pthread_mutex_t sinal;
extern int *MatrizRec; //Recursos disponiveis 
extern int **MatrizUso; //Recursos em uso
extern int **MatrizNec; //Recursos totais necessarios
extern int **MatrizFal; //Recursos solicitados

void Recdisp()  //PRINT
{
     for (int i = 0; i < R; ++i)
     {
          printf("%d, ",MatrizRec[i]); //printa os recursos disponíveis
     }

     printf("\n");
     return;
}

void Usodisp() //PRINT
{
     for (int i = 0; i < P; ++i)
     {
          printf("{ ");
          for (int j= 0; j < R; ++j)
          {
               printf("%d, ", MatrizUso[i][j]); //printa a matriz dos recursos em uso
          }
     printf("}\n");
     }
     return;
}

void Faldisp() //PRINT
{
    for (int i = 0; i < P; ++i)
     {
          printf("{ ");
          for (int j= 0; j < R; ++j)
          {
               printf("%d, ", MatrizFal[i][j]); //printa a matriz dos recursos em uso
          }
     printf("}\n");
     }
     return;
}

void reqlibdisp(int vec[])
{
     printf("O valor requisitado foi:\n");
     for (int i = 0; i < R; ++i)
     {
          printf("%d, ",vec[i]);
     }
     printf("\n");
     return;
}



int SeMaiorQueNec(int pID,int requisicao[])
{

     for (int i = 0; i < R; ++i) // Verifica se a requisicao eh menor ou igual que a MatrizFal
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

     for (int i = 0; i < R; ++i) // Verifica se a requisicao eh menor ou igual a MatrizRec
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

int modoseguro()
{
    //  int fimdorec[P] = {0}; // Verifica se passou por todos os recursos do processo
     int *fimdorec = calloc(P, sizeof(int));
    //  int recdisp[R]; // Rescurso que pode ser trabalhado no momento
    int *recdisp = calloc(R, sizeof(int));

     for(int i = 0; i < R; i++)
     {
          recdisp[i] = MatrizRec[i]; 
     }

     int k;
     for(int i = 0; i < P; i++)
     {
          if (fimdorec[i] == 0)
          {
               for(int j = 0; j < R; j++)
               {
                    // Verifica se ha recursos suficientes para fornecer a um processo
                    if(MatrizFal[i][j] <= recdisp[j])  
                    {             
                    /*Verifica se ha recursos suficientes para fornecer a um processo, caso haja quando chegar no terceiro tipo de recurso transforma 
                    a matriz de verificacao (fimdorec), em 1 e soma o que foi liberado pelo processo em questao para a matriz de recursos que podem 
                    ser trabalhados no momento. Apos isso zera o valor de i, uma vez que ha a possibilidade de um processo anterior que nao foi possivel 
                    alocar os recursos ser possivel agora.
                    */                    
	                    if(j==R-1)
                         {
                              fimdorec[i] = 1;

                              for (int k = 0; k < R; ++k)
                              {
                                   recdisp[k] += MatrizUso[i][k]; 

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
           
     for(int i = 0; i < P; i++) // Verifica se um processo nao foi possivel alocar recursos para ele, se nao retorna -1 e acusa o modo inseguro.
     {

          if (fimdorec[i] == 0)
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
     for (int i = 0; i < R; ++i) // Libera o recurso caso a o valor solicitado seja menor que o valor da MatrizUso
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



      


