Project 2
Authors: Jack Burns and Ian White

General Info:

	Implement priority scheduling equipped with an aging policy for optimization that increments the priority of each process in the readyqueue every time reschedule() is called.  The aging policy that we used was to increase the priority of every process by +1 when reschedule() is called [the policy provided in the project description].    

Lucid Description of test result(s):

	In our test case, we gave a process (process 2) a low priority to see it starve.  As one can observe, process 2 is the last process to execute because the other processes all had higher priorities than process 2, and therefore process 2 could not execute until the end.  Process 5, which had the largest priority executed completely before starting process 6, which had the 2nd largest priority, and so on.  When enabling aging, you can see that processes 5 and 6 dominate executing states for the first few reschedules, then the other processes with lower initial priorities begin to execute because their priorities are being iterated as they spend more time in the ready queue.  Once all of the processes are finished, the process with the greatest amount of "weight" [process 6] is left to run unopposed as it should with priority scheduling optimized using an aging policy.  Test results below.  

Test: AGING = FALSE

Hello XINU WORLD!
This is process 5 (PRINTER-C)
This is process 5 (PRINTER-C)
This is process 5 (PRINTER-C)
This is process 5 (PRINTER-C)
This is process 5 (PRINTER-C)
This is process 5 (PRINTER-C)
This is process 5 (PRINTER-C)
This is process 5 (PRINTER-C)
This is process 5 (PRINTER-C)
This is process 5 (PRINTER-C)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
bigargs(10, 20, 30, 40, 50, 60) == 210                                                                                   
This is process 3 (PRINTER-A)                                                                                            
This is process 3 (PRINTER-A)                                                                                            
This is process 4 (PRINTER-B)                                                                                            
This is process 4 (PRINTER-B)                                                                                            
This is process 4 (PRINTER-B)                                                                                            
This is process 2 (PRINTER-1)

__________________________________


Test: AGING = TRUE

Hello XINU WORLD!
This is process 5 (PRINTER-C)
This is process 6 (PRINTER-D)
This is process 5 (PRINTER-C)
bigargs(10, 20, 30, 40, 50, 60) == 210
This is process 5 (PRINTER-C)
This is process 6 (PRINTER-D)
This is process 3 (PRINTER-A)
This is process 5 (PRINTER-C)
This is process 4 (PRINTER-B)
This is process 6 (PRINTER-D)                                                                                            
This is process 5 (PRINTER-C)                                                                                            
This is process 2 (PRINTER-1)                                                                                            
This is process 5 (PRINTER-C)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 3 (PRINTER-A)                                                                                            
This is process 5 (PRINTER-C)                                                                                            
This is process 4 (PRINTER-B)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 5 (PRINTER-C)                                                                                            
This is process 5 (PRINTER-C)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 5 (PRINTER-C)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 4 (PRINTER-B)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)                                                                                            
This is process 6 (PRINTER-D)
