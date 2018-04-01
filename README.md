Ian White/Jack Burns
04/10/2017
CSCI-475

Project 3: Time Sharing and Synchronization

	In this portion of the project we implemented the Intel 8254 Programmable Interval Timer to cause interrupts every 10ms (length of our quantum).  This makes a context switch happen every 10ms.  We then implemented primitive spinlocks using mutex_t class.  If the lock is locked, the process trying to access it gets sent into a busy waiting loop until the lock is released.  Our implementation uses the test_and_set() method for atomicity.

	The second part of the project was to solve the dining philosophers problem using the tools that we implemented earlier in the project (i.e. hardware timer and spinlocks).

	The thing that we had the most trouble with was seeding our random number to provide us with good random values.  Another issue that we had was that during the print synchronization part prior to setting the spinlocks, I could not get the printout to print anything but "AAAAAAAAAABBBBBBBBBB" or "BBBBBBBBBBAAAAAAAAAA" unless I set the quantum size to 1 and made them print out 10 more times a piece.  I do not know if this was a result of my computer completing both processes before a context switch happend.
