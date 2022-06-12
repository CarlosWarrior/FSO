/*  KASSANDRA MONTEMAYOR ZAVALA
    CARLOS ALEJANDRO GUERRERO MARTINEZ
    Ejercicio 2 Actividad 4 : ******VOYEURISM***** 
    Programa donde un proceso padre con duracion de 20 segundos, crea a un 
    proceso hijo, con duracion de 1 segundo, y se observa que es lo que esta pasando

    REFRENCES:
            https://www.geeksforgeeks.org/getppid-getpid-linux/
            https://linuxhint.com/kill-system-call-in-c/
            https://www.csd.uoc.gr/~hy345/assignments/2013/cs345_front1.pdf
            https://www.gnu.org/software/libc/manual/html_node/Process-Completion.html#:~:text=as%20the%20argument.-,WNOHANG,as%20those%20that%20have%20terminated.
            https://www.freecodecamp.org/news/linux-list-processes-how-to-check-running-processes/

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
        sleep(20);
    }
    else
    {
        printf("Child Process ID: %d\n",getpid());
        sleep(1);

    }
}