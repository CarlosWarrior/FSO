#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void ejercicio3(int n){
  int root = getppid();
  int level = root;
  for(int c = 0; c <= n; c++){
    if(c == 0 || level != 0){
      //printf("Lvl %d, PID %d\n", c, level);
      printf("%d, PID %d\n", c, level);
      
      level = fork(); 
      if(level != 0){
        kill(level, SIGTERM);
      }
    }
  }
  return;
}

int main()
{
  printf("\nCon n = 1:\n",0);
  ejercicio3(1);
  printf("\nCon n = 2:\n",0);
  ejercicio3(2);
  printf("\nCon n = 4:\n",0);
  ejercicio3(4);
}