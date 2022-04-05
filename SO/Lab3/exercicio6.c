#include<stdio.h>
#include<pthread.h>
int num[50],quantidade,i;

void *primeira()
{
	int soma=0;
	float media;
	printf("Quantos números você quer colocar? ");
	scanf("%d",&quantidade);
	for(i=0;i<quantidade;i++)
	{
        printf("Coloque um número: ");
		scanf("%d",&num[i]);
	}
	for(i=0;i<quantidade;i++)
		{
			soma=soma+num[i];
		}
	media=soma/quantidade;
	printf("O valor médio é: %f",media);
}
void *segunda()
{


	int min=num[0];
	for(int i=1;i<quantidade;i++)
		{
			if(min>num[i])
			{
			min=num[i];
			}
		}
	printf("\nO valor mínimo é: %d",min);

}
void *terceira()
{

	int max=num[0];
	for(int i=1;i<quantidade;i++)
		{
			if(max<num[i])
			{
			max=num[i];
			}
		}
	printf("\nO valor máximo é: %d\n",max);
	}
int main()
{
int n;
pthread_t th1;
pthread_t th2;
pthread_t th3;
	n=pthread_create(&th1,NULL,&primeira,NULL);
	pthread_join(th1,NULL);

	n=pthread_create(&th2,NULL,&segunda,NULL);
        pthread_join(th2,NULL);
	
	n=pthread_create(&th3,NULL,&terceira,NULL);
        pthread_join(th3,NULL);

}