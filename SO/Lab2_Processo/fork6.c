#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  int pid, pid1;

  if ((pid = fork())> 0)  
    if ((pid1 = fork()) > 0){
       //wait(NULL);
       printf("\nProcesso A %d\n",getpid());}
    else{
       printf("\nProcesso C%d\n",getpid());}
  else{  
       printf("\nProcesso B%d\n",getpid());}

  return 0;
}
