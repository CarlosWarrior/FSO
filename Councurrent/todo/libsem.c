#include <pthread_utils.h>
#include <stdlib.h>
#include <libsem.h>
#include <stdio.h>

// Macro que incluye el código de la instrucción máquina xchg
#define atomic_xchg(A,B) 	__asm__ __volatile__(	\
							"   lock xchg %1,%0 ;\n"	\
							: "=ir"  (A)			\
							: "m"  (B), "ir" (A)		\
							);

int g=0;


SEMAPHORE semaphore_get(int val)
{
	printf("semaphore_get");
	// Solicitar memoria dinámica para una struct STRSEMAPHORE usando malloc
	SEMAPHORE s = malloc(sizeof(struct STRSEMAPHORE));
	// Inicializar el contador del semáforo con el valor de val
	s->count = val;
	// Crear una cola (ver función queue_create()) y asignarla al apuntador de la cola en el semáforo
	s->queue = queue_create();
	return(s);
}

void semaphore_destroy(SEMAPHORE s)
{
	printf("semaphore_destroy");
	// Destruir la cola
	queue_destroy(s->queue);
	// Liberar la memoria del semáforo
	free(s);
}

void semaphore_wait(SEMAPHORE s)
{
	printf("semaphore_wait");
	int local = 1;
	do { atomic_xchg(local,g); } while(local==1);
	// Aquí debes implementar la función semaphore_wait() haciendo que el hilo que tiene que esperar se bloquée de manera que no haya espera ocupada
	//	- Antes de bloquearlo hay que:
	//	-	1.- Obtener el tid del hilo (pthread_self) y guardarlo en una variable.
	int tid = pthread_self();
	//	-	2.- Guardar el tid en la cola del semáforo con queue_offer
	queue_offer(s->queue, tid);
	s->count++;
	//Un detalle muy importante es que antes de que el hilo se bloquée, debe liberar el atomic_xchg()
	g = 0;
	local = 1;
	//	-	3.- Finalmente bloquear al hilo (block_thread)
	block_thread();
}

void semaphore_signal(SEMAPHORE s)
{
	printf("semaphore_signal");
	int local = 1;
	do { atomic_xchg(local,g); } while(local==1);
	// Aquí hay que implementar la función semaphore_signal() para que un hilo que esté bloqueado en
	// el semáforo s->queue se desbloquée y se actualize el contador del semáforo-
	// Recuerda que esta función debe ejecutarse de manera atómica
	int tid = pthread_self();
	pthread_t polled = queue_poll(s->queue);
	s->count--;
	g = 0;
	local = 1;
	unblock_thread(polled);
}


