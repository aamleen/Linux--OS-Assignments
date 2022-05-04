Instructions to run the program: just give make command and then ./main. Ctrl+C to stop the indefinite process.

Logic/Reasoning:
    The whole Question is based on creating 3 child processes from 1 parent process(main). It was so designed that first the parent process will call fork and create a child process S1. In this, I have first given a signal handler to the signal SIGTERM which will be called from the other processes. All the signal-handlers are provided by using sigaction. In the sigaction, the saflag is set to SIG_INFO, because we will be requiring the data sent by the signals via sigqueue from other processes.
   Then I went on to create 2 more processes: SR & ST, then with the help of execv(), I replaced them with the programs E1 & E2 respectively, and also passed the pid of S1 to both of them as an argument. 
   **S1 signal handler discussed at last 

In SR Process:
	When the SR process works, I had first set the signal-handler of the SIGALRM signal using sigaction. Then I had set the itimer so that it gets invoked initially at 1 sec and then repeatedly at an interval of 1 sec. Then using setitimer(), I had set the timer to send SIGALRM signals at the given intervals in itimerval. 
    In the handler of SR-SIGALRM, I had generated a random no. using rdrand instruction in inline assembly. Then saved the same to rand_no. Then I had printed the random no. in SR(just for verification) & then I enqueue it and then pass the same to S1 with the signal as SIGTERM using sigqueue. This will invoke the signal handler in S1(discussed earlier).

In ST Process:
	When the ST process works, I had set the signal-handler of the SIGTERM and SIGALRM signals using sigaction(). Then as done is SR, I had the set time-intervals after which SIGALRM signal will be passed to the same process, thereby invoking the signal handler.
    In SIGALRM signal handler, I had generated the CPU time-stamp counts using rdtsc instruction. Then I divided the same with my CPU frequency which will then return the total seconds since the CPU was made on. With some basic time-manipulation, I convert the total secs to the overall hrs, mins and secs. Then I formed a string which has the format hh:mm:ss. 
    Then, I had created a shared-memory (created a unique key of the memory with ftok, then with that key and shmid() function, I created a shared memory, whose ID is stored in shmid. Then the current process(ST) is attached to the shared memory using shmat(), which returns a pointer to the mem-address) Then I copy the generated time(string) to the shared memory. Also using sigval and sigqueue(), I pass a pointer of the current time string to the own SIGTERM handler. For the S1 SIGTERM handler, I pass a value "-69" to the handler when giving the same signal through sigqueue(), so that it identifies that the calling process is ST, as SR will never pass -ve nos. since its unsigned long.    In SIGTERM handler of ST, I just print the recieved string via the pointer in siginfo.  

S1 SIGTERM Handler:
	When any process sends the SIGTERM signal, the handler will be invoked. If it is ST(siginfo sigval value is -69) then the earlier shared memory will be opened and attached to the process using the same key and earlier mentioned methods. Then the data(time-string) is read from the same and printed. Then the shared memory is detached and deleted.
   If the call was from SR, then the passed random no. is printed.
