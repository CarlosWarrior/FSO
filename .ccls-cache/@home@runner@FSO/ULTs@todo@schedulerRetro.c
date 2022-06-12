#include <scheduler.h>

extern THANDLER threads[MAXTHREAD];
extern int currthread;
extern int blockevent;
extern int unblockevent;

QUEUE ready;
QUEUE waitinginevent[MAXTHREAD];

void scheduler(int arguments)
{
	int old,next;
	int changethread=0;
	int waitingthread=0;
	
	int event=arguments & 0xFF00;
	int callingthread=arguments & 0xFF;

	if(event==NEWTHREAD)//Any new thread will enqueue the current threand and will be given a time block
	{
		threads[callingthread].status=READY;		
		_enqueue(&ready,callingthread);
	}
	
	if(event==BLOCKTHREAD)
	{

		threads[callingthread].status=BLOCKED;//Any blocked thread will be added to waiting queue and thread will change
		_enqueue(&waitinginevent[blockevent],callingthread);

		changethread=1;
	}

	if(event==ENDTHREAD)
	{
		threads[callingthread].status=END;//Any finished thread will change thread
		changethread=1;
	}
	
	if(event==UNBLOCKTHREAD)
	{
			threads[callingthread].status=READY;//Any unblocked thread will enqueue thecurrent threand and will be given a time block
			_enqueue(&ready,callingthread);
	}

	if(event==TIMER)
	{
		threads[callingthread].status=READY;//Any time block ended will enqueue the current thread into ready line and will change threads
		_enqueue(&ready, callingthread);
		changethread=1;
	}
	
	if(changethread)
	{
		old=currthread;
		next=_dequeue(&ready);
		
		threads[next].status=RUNNING;
		_swapthreads(old,next);
	}

}