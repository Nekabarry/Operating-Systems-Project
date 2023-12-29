# Operating-Systems-Project
CPU Scheduler Simulator

1. Program should have command argument options to get input data from a text file and command argument option for write output data. “-f” must be used for command argument and following text indicate input file name and “-o” for output file name.
      student@db:~$ ./cpe351 –f input.txt –o output.txt
  
2. This file should have three columns and unlimited rows. It must be text and fields should delimit by “:” character. Below table represent structure of this file.
   
BurstTime ArrivalTime Priority
10           0         0 
5            0         0

Some data fields may not use at decision process so you can omits the values. But every process should have three of these values. At the Appendix section input.txt file given as example.
       
    
4. After first time executing simulator should ask for user to choose scheduling method. Menu should have at least four options.
   
   CPU Scheduler Simulator
1) SchedulingMethod(None)
2) PreemptiveMode(Off)
3) ShowResult
4) End Program
Option >

a) Scheduling Method: In this mode program optain scheduling method from user. You should implement:
- None: None of scheduling method chosen
-First Come, First Served Scheduling
- Shortest-Job-First Scheduling
- Priority Scheduling
-Round-Robin Scheduling (You should also obtain time quantum value)

b) Preemptive Mode: This is a clock-driven mode, in which the clock is a counter that is incremented each simulated second. The clock is initially 0, and continues "ticking" until all the jobs in the input have been serviced and left the system. This simulation runs until a particular number of jobs have been serviced.

Non-preemptive Mode: In this mode dispatcher should make decision after running process was terminated.
c) Show Result: If user chooses this option, program shows report to user from screen (As described Step 4).

d) End Program: If user chooses this option, program show all (implemented) scheduling results on display (As described Step 4) and also write these results to output file that given with “-o” option and terminate simulator.

e) Appendix section has screen and file outputs. Please create same output for your program.

4. Your program must gather statistics, compute, and report the following information:
a) The average waiting time that all jobs spend in the wait queue.
b) The waiting time that each job spends in the wait queue.

5. You can get more information for CPU Scheduling methods from your text book (chapter 5). Some Scheduling methods not run in Preemptive mode. So take care about it.
