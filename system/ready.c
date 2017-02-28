/* ready.c - ready */

#include <xinu.h>

struct queue *readyqueue;	/** ready queue */


/**
 * Put process on ready queue
 * @param pid	ID of process to place on ready queue
 * @param resch	reschedule afterward?
 */
status	ready(pid32 pid, bool8 resch)
{
	register struct procent *prptr;

	if (isbadpid(pid))
		return(SYSERR);

	// set process state to indicate ready and add to ready list
	prptr = &proctab[pid];	

	// TODO - set the process' state pointed by prptr to "ready"
	prptr->prstate = PR_READY;	

	// TODO - enqueue the process
<<<<<<< HEAD
	printqueue(readyqueue);
	//kprintf("\nPidBefore: %d", pid);
	pid = enqueue(pid, readyqueue);
	//kprintf("\nSize: %d\n", size(readyqueue));
	//kprintf("\nHead: %d\n", readyqueue->head->pid);
	//kprintf("\ntail: %d\n", readyqueue->tail->pid);
	//kprintf("\nPidAfter: %d", pid);
	//printqueue(readyqueue);
	//kprintf("\nSize: %d\n", size(readyqueue));
=======
	pid = enqueue(pid, readyqueue);
>>>>>>> b34c4ad5956d3de95e09c1ba93a5114bebcb7f93

	if (resch == RESCHED_YES)
		resched();

	return OK;
}
