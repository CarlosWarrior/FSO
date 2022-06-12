/*  KASSANDRA MONTEMAYOR ZAVALA
    CARLOS ALEJANDRO GUERRERO MARTINEZ
    Ejercicio 4 Actividad 4 : ******INVERTED VOYEURISM***** 
    Desarrolla un programa que al ejecutarse cree dos procesos hijos y cada uno de los hijos creará 3 nuevos procesos hijos. De esta manera habrá un proceso padre, dos procesos hijos y seis procesos nieto. Los hijos y los nietos deberán tener al final la instrucción sleep(20), pero el padre después de ejecutar la instrucción sleep(5) deberá terminar a todos los hijos y nietos.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
  int c = 0;

  int root = getppid();
  int parent;
  printf("Root process %d\n", root);
  while(c<2){
    c++;
    if(getppid() == root){
      printf("Creating Child process %d\t%d\n", c,getppid());
      parent = fork();
      sleep(1);
    }
    if(parent != 0){
      int g = 0;
      while(g<3 && getppid() == root){
        g++;
        printf("Creating Grandchild process %d | parent %d: %d\n", g, c, parent);
        int grandchild = fork();
        sleep(1);
      }
    }
  }
  sleep(5);
}