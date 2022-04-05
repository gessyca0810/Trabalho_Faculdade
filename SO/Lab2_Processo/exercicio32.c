#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>

int main()
{    
    pid_t pid;
    pid = fork();

    sleep (10);
    if (pid < 0)
    {
        perror("erro:");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("Eu sou o processo filho, irei sair daqui.\n");
        exit(0);
    }
    printf("Sou o processo filho %d, vou ser um processo zumbi por 10 segundos.\n", pid);

    sleep(10);

    system("ps -opid,ppid,state,tty,command");
    printf("Processo pai saiu.\n");
    return 0;
}