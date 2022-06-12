/*  KASSANDRA MONTEMAYOR ZAVALA
    CARLOS ALEJANDRO GUERRERO MARTINEZ
    Ejercicio 1 Actividad 4 : ******PATRICIDE***** 
    programa donde un proceso padre crea un proceso hijo, 
    y al iniciar el proceso hijo, este debera matar a su padre
    REFRENCES:
            https://www.geeksforgeeks.org/getppid-getpid-linux/
            https://linuxhint.com/kill-system-call-in-c/
            https://www.csd.uoc.gr/~hy345/assignments/2013/cs345_front1.pdf

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    int p = fork();
    if(p!=0)
    {
        printf("Parent Process ID: %d\n",getpid());
    }
    else
    {
        printf("Parent Process ID: %d \t Child Process ID: %d\n",
        getppid(),getpid());
        kill(getppid(),SIGTERM);

    }
}