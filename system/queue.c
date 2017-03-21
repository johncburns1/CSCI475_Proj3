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
	return q->size;
}

/**
 * Prints out contents of a queue
 * @param q	pointer to a queue
 */
void	printqueue(struct queue *q)
{	
	struct qentry *node = q->head;
	kprintf("\n");
	
	while (node != NULL)
	{

		//if there is only 1 element
		if(q->head == node && q->tail == node)
		{
			kprintf("[(pid=%d, key=%d)]. ", node->pid, node->key);
		}
		
		//1st process
		else if(q->head == node) 
		{
			kprintf("[(pid=%d, key=%d), ", node->pid, node->key);
		}
		
		//last process
		else if(q->tail == node)
		{
			kprintf("(pid=%d, key=%d)].\n", node->pid, node->key);	
		}
		
		//every other process
		else 
		{
			kprintf("(pid=%d, key=%d), ", node->pid, node->key);
		}

		node = node->next;
	}
	
	kprintf("\n");
}

/**
 * Checks whether queue is empty
 * @param q	Pointer to a queue
 * @return TRUE if true, FALSE otherwise
 */
bool8	isempty(struct queue *q)
{
	//TODO
	if(q->head == NULL) {
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
 * @param key	priority key of process
 *
 * @return pid on success, SYSERR otherwise
 */
pid32 enqueue(pid32 pid, struct queue *q, int32 key)
{
        //TODO - check if queue is full and if pid is illegal, and return SYSERR if either is true
	if(isfull(q) == TRUE || isbadpid(pid) == TRUE) {
		return SYSERR;
	}
        
	//TODO - allocate space on heap for a new QEntry
	struct qentry *newentry = (struct qentry*) malloc(sizeof(struct qentry));

        //TODO - initialize the new QEntry
	newentry->pid = pid;
	newentry->key = key;		

	if(isempty(q) == TRUE) {
		newentry->prev = NULL;
		newentry->next = NULL;
		q->head = newentry;
		q->tail = newentry;
	}
	
	else {
		if(key > q->head->key)
		{
			//kprintf("First element here has priority %d\n", key);
			newentry->next = q->head;
			newentry->prev = NULL;
			q->head = newentry;
			newentry->next->prev = newentry;
			
		}
		
		else 
		{
			struct qentry *iter = q->head;
			int cont = 1;
	
			//iterate throught the queue
			while(iter != NULL && cont == 1) {
				
				//regular case
				if(iter->key < key) {
					//kprintf("%d is greater than %d\n", key, iter->key);
					newentry->next = iter;
					newentry->prev = iter->prev;
					newentry->prev->next = newentry;
					iter->prev = newentry;
					cont = 0;
				}

				//the tail
				else if(iter->next == NULL)
				{
					newentry->prev = q->tail;	
					newentry->next = NULL;
					q->tail->next = newentry;
					q->tail = newentry;
					cont = 0;
				}
				
				//TODO - find the qentry with the given pid
				else {
					//kprintf("%d is NOT greater than %d\n", key, iter->key);
					iter = iter->next;
				}
			}
		}
	}

        //TODO - return the pid on success
	//printqueue(q);
	q->size++;	
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
		kprintf("\nIs empty on dequeue\n");
		return EMPTY;
	}

	else {
	        //TODO - get the head entry of the queue
		struct qentry *swapper = q->head;
		xpid = q->head->pid;
		
		//TODO - unlink the head entry from the rest
		q->head = q->head->next;

		//TODO - free up the space on the heap
		q->size--;
		free(swapper, sizeof(swapper));
	}	

       
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

	struct qentry *iter = q->head;
	
	//if first element
	while(iter != NULL) {
		
		if(iter->pid == pid) {
			return iter;
		}

		//TODO - find the qentry with the given pid
		else {
			iter = iter->next;
		}
	}

	return NULL;
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
	
	pid32 pid = q->tail->pid;
	
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
	//TODO - return EMPTY if queue is empty
	if(isempty(q)) {
		return EMPTY;
	}
	
	//TODO - return SYSERR if pid is illegal
	if(isbadpid(pid) == TRUE) {
		return SYSERR;
	}
	
	else {
		
		//buffers for removal
		struct qentry *entry = getbypid(pid, q);
		struct qentry *buffer = entry->next;
		
		//TODO - remove process identified by pid parameter from the queue and return its pid
		entry->prev->next = buffer;
		buffer->prev = entry->prev;
		free(entry, sizeof(entry));
		return pid;		
	}
}
