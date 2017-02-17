/* queue.c - enqueue, dequeue, isempty, nonempty, et al. */

#include <xinu.h>
#include <stdlib.h>

/**
 * Size of the queue
 *
 * @param q pointer to a queue
 * @return int32 size of queue
 */
int32 	size(struct queue *q)
{
	//queue is empty
	if(isempty(q) == TRUE) {
		return 0;
	}

	//queue has only one element
	else if(q->head == EMPTY) {
		return 1;
	}

	else {
		return sizehelper(q->head);
	}
}

/**
 * Size helper method
 *
 * @param struct qentry* entry
 * @return int32 size
 */
int32 sizehelper(struct qentry* entry) {
	
	//base case
	if(entry->next == EMPTY) {
		return 1;
	}

	else {
		return sizehelper(entry->next) + 1;
	}
}

/**
 * Prints out contents of a queue
 * @param q	pointer to a queue
 */
void	printqueue(struct queue *q)
{
	//TODO - print all contents from head to tail
	//TODO - format should be [(pid=p1), (pid=p2), ...]
	
	//queue is empty
	if(isempty(q) == TRUE) {
		kprintf("\nQueue is empty\n");
	}

	//queue has only one element
	else if(q->head->next == EMPTY) {
		kprintf("[(pid=%d)].\n", q->head->currpid);
	}

	else {
		printhelper(q->head->next);
	}
}

/**
 * Printqueue helper method
 *
 * @param struct qentry* entry
 */
void printhelper(struct qentry* entry) {
	
	//base case
	if(entry->next == EMPTY) {
		kprintf("[(pid=%d)].", entry->currpid);
	}

	else {
		kprintf("[(pid=%d)], ", entry->currpid);
		printhelper(entry->next);
	}
}

/**
 * Checks whether queue is empty
 * @param q	Pointer to a queue
 * @return TRUE if true, FALSE otherwise
 */
bool8	isempty(struct queue *q)
{
	//TODO
	if(q->head == EMPTY) {
		return TRUE;
	}
	return FALSE;
}

/**
 * Checks whether queue is nonempty
 * @param q	Pointer to a queue
 * @return TRUE if true, FALSE otherwise
 */
bool8	nonempty(struct queue *q)
{
	//TODO - don't just check q's size because q could be NULL
	if(isempty(q) == TRUE) {
		return FALSE;
	}
	return TRUE;
}


/**
 * Checks whether queue is full
 * @param q	Pointer to a queue
 * @return TRUE if true, FALSE otherwise
 */
bool8	isfull(struct queue *q)
{
	//TODO - check if there are at least NPROC processes in the queue
	if(size(q) >= NPROC) {
		return TRUE;
	}

	return FALSE;
}


/**
 * Insert a process at the tail of a queue
 * @param pid	ID process to insert
 * @param q	Pointer to the queue to use
 *
 * @return pid on success, SYSERR otherwise
 */
pid32 enqueue(pid32 pid, struct queue *q)
{
        //TODO - check if queue is full and if pid is illegal, and return SYSERR if either is true
	if(isfull(q) == TRUE || isbadpid(pid) == TRUE) {
		return SYSERR;
	}
        
	//TODO - allocate space on heap for a new QEntry
	struct qentry *newentry = (struct qentry*) malloc(sizeof(struct qentry*));

        //TODO - initialize the new QEntry
	newentry->currpid = pid;
	
	newentry->prev = q->tail;
	newentry->next = EMPTY;
	q->tail->next = newentry;
	
	//TODO - insert into tail of queue
	q->tail = newentry;

        //TODO - return the pid on success
	return pid;
}


/**
 * Remove and return the first process on a list
 * @param q	Pointer to the queue to use
 * @return pid of the process removed, or EMPTY if queue is empty
 */
pid32 dequeue(struct queue *q)
{
	pid32 xpid = 0;

        //TODO - return EMPTY if queue is empty
	if(isempty(q) == TRUE) {
		return EMPTY;
	}

        //TODO - get the head entry of the queue
	struct qentry *newhead = EMPTY;

        //TODO - unlink the head entry from the rest
	xpid = q->head->currpid;
	newhead = q->head->next;

        //TODO - free up the space on the heap
	free(q->head, sizeof(q->head));
	q->head = newhead;	

        //TODO - return the pid on success
	return xpid;
}


/**
 * Finds a queue entry given pid
 * @param pid	a process ID
 * @param q	a pointer to a queue
 * @return pointer to the entry if found, NULL otherwise
 */
struct qentry *getbypid(pid32 pid, struct queue *q)
{
	//TODO - return NULL if queue is empty or if an illegal pid is given
	if(isempty(q) == TRUE || isbadpid(pid) == TRUE) {
		return NULL;
	}
	
	//if first element
	if(pid == q->head->currpid) {
		return q->head;
	}

	//TODO - find the qentry with the given pid
	else {
		getbypidhelper(pid, q->head->next);
	}
}

/**
 * Recursive helper for findbypid method
 * @param pid	a process ID
 * @param q	a pointer to a qentry
 * @return pointer to the entry if found, NULL otherwise
 */
struct qentry *getbypidhelper(pid32 pid, struct qentry* entry) {

	//base case
	if(pid == entry->currpid) {
		return entry;
	}

	//TODO - find the qentry with the given pid
	else {
		getbypidhelper(pid, entry->next);
	}
}

/**
 * Remove a process from the front of a queue (pid assumed valid with no check)
 * @param q	pointer to a queue
 * @return pid on success, EMPTY if queue is empty
 */
pid32	getfirst(struct queue *q)
{
	//TODO - return EMPTY if queue is empty
	if(isempty(q)) {
		return EMPTY;
	}

	//TODO - remove process from head of queue and return its pid
	else {
		return dequeue(q);
	}
}

/**
 * Remove a process from the end of a queue (pid assumed valid with no check)
 * @param q	Pointer to the queue
 * @return pid on success, EMPTY otherwise
 */
pid32	getlast(struct queue *q)
{
	//TODO - return EMPTY if queue is empty
	if(isempty(q)) {
		return EMPTY;
	}
	
	pid32 pid = q->tail->currpid;
	return remove(pid, q);
}



/**
 * Remove a process from an arbitrary point in a queue
 * @param pid	ID of process to remove
 * @param q	Pointer to the queue
 * @return pid on success, SYSERR if pid is not found
 */
pid32	remove(pid32 pid, struct queue *q)
{
	struct qentry *buffer = EMPTY;
	
	//TODO - return EMPTY if queue is empty
	if(isempty(q)) {
		return EMPTY;
	}
	
	//TODO - return SYSERR if pid is illegal
	if(isbadpid(pid) == TRUE) {
		return SYSERR;
	}
	
	else {
		struct qentry* entry = getbypid(pid, q);
		//TODO - remove process identified by pid parameter from the 		queue and return its pid
		buffer = entry->next;
		entry->prev->next = buffer->next;
		entry->next->prev = buffer->prev;
		free(entry, sizeof(entry));
		return pid;		
	}
}


int main() {
	struct queue *q = newqueue();
	enqueue(1, q);
	printqueue(q);
	kprintf("\nSize: %d\n", size(q));
	enqueue(100, q);
	printqueue(q);
	kprintf("\nSize: %d\n", size(q));
}

