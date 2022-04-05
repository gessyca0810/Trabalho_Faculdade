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

int R; //Quantidade de tipos de recursos 
int P; //Quantidade de processos

pthread_mutex_t sinal;
int *MatrizRec; //Recursos disponiveis 
int **MatrizUso; //Recursos em uso
int **MatrizNec; //Recursos totais necessarios
int **MatrizFal; //Recursos solicitados
int i = 0; 
int j = 0;

void Recdisp()  //PRINT
{
     for (i = 0; i < R; ++i)
     {
          printf("%d, ",MatrizRec[i]); //printa os recursos disponíveis
     }

     printf("\n");
     return;
}

void Usodisp() //PRINT
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

void Faldisp() //PRINT
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

void reqlibdisp(int vec[])
{
     printf("O valor requisitado foi:\n");
     for (i = 0; i < R; ++i)
     {
          printf("%d, ",vec[i]);
     }
     printf("\n");
     return;
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

int modoseguro()
{
    //  int fimdorec[P] = {0}; // Verifica o status do processo (seguro ou nao)
     int *fimdorec = calloc(P, sizeof(int)); 
    //  int recdisp[R]; // Rescurso que pode ser trabalhado no momento
    int *recdisp = calloc(R, sizeof(int));

     for(i = 0; i < R; i++) 
     {
          recdisp[i] = MatrizRec[i]; 
     } 
     int k;
     for(i = 0; i < P; i++) //Percorre todos os processos
     {
          if (fimdorec[i] == 0)
          {// Verifica se ha recursos suficientes para fornecer a um processo
               for(j = 0; j < R; j++)
               {
                    /*Verifica se ha recursos suficientes para fornecer a um processo, caso haja quando chegar no terceiro tipo de recurso transforma 
                    a matriz de verificacao (fimdorec), em 1 e soma o que foi liberado pelo processo em questao para a matriz de recursos que podem 
                    ser trabalhados no momento. Apos isso zera o valor de i, uma vez que ha a possibilidade de um processo anterior que nao foi possivel 
                    alocar os recursos ser possivel agora.
                    */
                    if(MatrizFal[i][j] <= recdisp[j])  
                    {                                 
	                    if(j==R-1)
                         {
                              fimdorec[i] = 1;

                              for (k = 0; k < R; ++k)
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
           
     for(i = 0; i < P; i++) // Verifica se um processo nao foi possivel alocar recursos para ele, se nao retorna -1 e acusa o modo inseguro.
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
     Recdisp();
     printf("Metrix Allocated:\n");
     Usodisp();
     printf("Metrix Need:\n");
     Faldisp();
     return 0;
}

void *processos(void* processosID) // Faz a chamada de requisicao e liberacao dos recursos para os processos
{     
     int pID = *(int*)processosID; 
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


