# OSN Assignment 5

## Implementation

### Task 1 

#### Waitx

The waitx system call was mostly created as a mirror of the already defined wait() syscall. However, the input parameters of wtime and rtime had to be updated. This was done by extending the struc proc structure to include fields ctime, etime, and rtime. rtime was directly equivalent to the 2nd parameter of waitx(), and was implemented by incrementing its value at each clock tick in trap.h . wtime was calculated with the help of 2 new parameters, rchktime and tot_wtime. Here, rchktime noted the last time when a process changed to state 'RUNNABLE', as we only consider waiting time as the time it spends as 'RUNNABLE'. Once it transitions to another state, the current time - rchktime is incremented to tot_wtime, which stores the wtime required in waitx(). The user command 'time' can be used to run waitx for a function, which it does using fork() and execvp.

#### ps

The ps user program displays the details of all processes that are defined, i.e., not in state 'UNUSED'. This is done with the help of a system call pinfo(), which iterates over the entire ptable, and once it finds a process with pid not equal to 0, it outputs all the details appropriately. These details are mostly stored as extensions of the current proc structure, which will be further elaborated on in the upcoming segments. In addition, basic error checking and output alignment using '\t' has been done.

### Task 2

#### FCFS Scheduler

FCFS scheduler works on a non-preemptive basis. As the name suggests, it is first come first serve logic, and processes are executed in their entirety on the basis of when they were first created. This is implemented by using ctime, added by us in proc structure in task 1. Every iteration of the loop we find the process with the earliest creation time and execute it.

#### Priority Based Scheduler

PBS works on the principal of executing processes having the highest priority, and in case of a tie, in a round robin fashion. The priority is added as an extension to the proc structure, and can be modified with the help of the set_priority() system call, that accounts for errors and updates the value accordingly. As PBS is preemptive in nature, we have to ensure that before a process is selected, we check for lower priority each time. This is implemented by iterating through the ptable, and before selecting a process, we iterate and find the minimum priority. If the priority is minimum, then the chosen process is executed, else it iterates through the ptable again.

#### Multi-Level Feedback Queue

Multi-Level feedback queue uses 5 different priority queues to control the order of execution. It is preemptive in nature. The queues are not implemented separately. Instead, the proc structure has been extended to include a pointer to another proc struct. Thus, the queues have been implemented by using linked lists. Push and pop have been implemented as different functions using standard logic of linked lists, and we have 5 extra proc structures that denote the head of each queue. The processes are chosen in order from queues in higher to lower priorities, and their CPU time is monitored in trap.c. In case the elapsed run time exceeds the given number of ticks, then the process is preempted and shifted to a lower queue. On initialization, all processes are pushed into the highest priority queue, and all those waking from sleep into the original queue, using the push() call. Aging is also implemented in the scheduler, by iterating through all queues, and for all processes exceeding the age threshhold, which over here is 30, they are demoted from the given queue to a lower queue. This is again done using linked list and pointer structures. It is ensured that there are no dangling pointers or extra/unnecessary memory left allocated.

## Performance Analysic

### Round Robin Scheduler

Average Waiting Time :	120 ticks
Average Running Time :	10 ticks
Total Benchmark Time :	1100 ticks

This performance of round robin scheduler can be expected for the given benchmark tests. As we are preempting many processes frequently so as to give equivalent timeslice to each and every process, our average waiting time increases and comes out to the given value. The runtime is also expected as due to the high amount of swapping, the runtime is slightly more than that of FCFS, which is non-preemptive, and PBS where there was observed to be low runtime. This scheduling is able to perform the best in terms of total time out of all the implemented schedulers.

### First Come First Serve Scheduler

Average Waiting Time :	1 tick
Average Running Time :	8 ticks
Total Benchmark Time :	1250 ticks

The firstcome first serve scheduler apparently seems to have very less wait time as the processes are mostly waiting in sleeping state, rather than runnable which is detected by the waitx call. As a result, the average wait time comes out to be very less. The runtime is also slightly less than RR as the processes arent preempted but execute till completion. In terms of performance, it is better than PBS, worse than round robin, and is on average equivalent to MLFQ, albeit more stable in terms of total time.

### Priority Based Scheduler

Average Waiting Time :	1 tick
Average Running Time :	7 ticks
Total Benchmark Time :	1350 ticks

Priority based scheduler has an equivalent output to that of FCFS scheduler. This can be concluded from the fact that despite there being preemption, by choosing based on priority, wait time is very less, and it switches less between processes. Overall, it had the poorest performance in comparison to all schedulers. This can partially be inferred from the method of implementation, as the overhead required to ensure priority with preemption far outweighed the increased throughput of the scheduling algorithm.

### Multi-level Feedback Queue

Average Waiting Time :	150 ticks
Average Running Time :	15 ticks
Total Benchmark Time :	1250 ticks

Multi level feedback queue had performance slightly resembling RR. The high wait time can be logically followed from the fact that many processes were waiting for execution in RUNNABLE state in the different priority queues. Due to the strict requirements in terms of timeslice for each queue, we can see that processes get preempted often in this scheduler, and thus there is a lot of demotion and aging observed in the benchmark. In terms of performance, it performed worse than round robin, but better than priority based. It was equivalent to first come first serve, but had more variance in its results. Often, the total time would vary even as close as RR and PBS, with the average value nearing that of FCFS.

Thus, overall we observe that in terms of performance, RR < MLFQ = FCFS < PBS. 

