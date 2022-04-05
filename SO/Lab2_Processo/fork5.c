/*
 Quantos processos serão criados?
*/ 


#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {

int pid;
	pid = fork();
	if (pid == 0)
	{
		fork();
		fork();
	}
	printf("PID = %d\n", getpid());
return 0;
} 
