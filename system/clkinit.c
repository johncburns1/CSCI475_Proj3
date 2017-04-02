/* clkinit.c - clkinit */

#include <xinu.h>
#include <interrupt.h>
#include <clock.h>

uint32	clktime;		/* seconds since boot			*/
uint32	ctr1000 = 0;		/* milliseconds since boot		*/
uint32	preempt;		/* preemption counter			*/

/**
 * Initialize the clock at system start up
 */
void	clkinit(void)
{
	// TODO -- program the timer!
	// 	Use Counter 0, 16-bit binary counter, rate generator mod, read/write
	//	least significant byte first, followed by most significant byte
	uint16 controlWord = 0x34; //00110100
	outb(CLKCNTL, controlWord);

	// TODO -- set initial value of the countdown!
	//	We want to set countdown in such a way that
	//	the timer goes off every 1ms
	uint16	countdown = 0x4A9; //1193

	//cut off the top 8 bits
	unit16	leastSig = countdown & 0x00FF;	
	
	//cut off the first 8 bits and then shift them right
	unit16	mostSig = countdown & 0xFF00;
	mostSig >>= 8;

	// TODO -- Now program the initial value for countdown
	// 	must write in two operations
	outb(CLOCK0, leastSig);	//write least significant byte of countdown
	outb(CLOCK0, mostSig);	//write most significant byte of countdown


	// Set interrupt vector for clock to invoke clkint
	set_evec(IRQBASE, (uint32)clkint);

	preempt = QUANTUM;	// initial time quantum

	clktime = 0;		// start counting seconds

	return;
}
