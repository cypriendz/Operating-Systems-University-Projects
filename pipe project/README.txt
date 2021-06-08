YOUTUBE LINK: https://youtu.be/TpbI8mQ1a_U

MAIN FUNCTION: The main function runs the program. First I create an array of pthreads_t that has a size of 200. This array will hold all the phonecall threads. Then I decare an int called debateTime and
initialize it to the command line input given to the program. atoi() function takes the input and converts it to a useable int value. Then I create the thread that will be for the timer function, this being timerID. Next I initalize all the semaphores using sem_init. The semaphore for idLock and connected_lock are are both binary semaphores therefore their last argument of sem_init() is 1,
meaning only one thread can access a critical region at a time giving these two semaphores. The last argument for sem_init() in regards to operators semaphore is 2/ NUM_OPERATORS, because we are
allowed to have two threads access a critical region for this semaphore. After initalizing the semaphores, the program creates the 200 phonecall threads using a loop that
goes 200 times, and creates a new thread/phonecall within each loop using pthread_create(). The TID of each of these threads is stored in the calls[] pthread array(first argument of the
pthread_create()), and the thread being executed is of course phonecall (the third argument of the pthread_create()) since we need to create 200 phonecalls. Once we do this, we create the timer thread that causes the main thread to wait a certain amount of time, which is given by a command line input(&debateTime/fourth
argument of this pthread_create()). We create this timer thread with pthread_create(), and the TID of the timer thread is held witin timerID variable(first argument of this pthread_create()). Since this thread created is supposed to run the timer function, we pass in timer as the second argument of this pthread_create(). After creating this thread, we tell the main thread to wait until the timer thread is finished, this is done with pthread_join(). Since we are waiting for the timer thread to finish, timerID is passed into the first argument of pthread_join since this variable holds the ID of our timer thread. Then we destroy all the semaphores we created by using the sem_destroy() function, and passing in the semaphore variable names as the arguuments of the sem_destroy() calls to tell the program which semaphores to kill. And finally, we kill the program as well as all the phonecall threads by making a call to exit(0)

PHONECALL FUNCTION/THREAD: This is the function for the phone call thread. First we create a local int variable called callerID that will hold a value between 1-200, the 1-200 comes from next_id global
variable. We next increment next_id so that no two threads will have the same callerID. The program then prints that this thread "is attempting to connect...". All of this is done within the binary sempaphore idLock, so
that a race condition will not occur for the incrementing and assigning of next_id and the print statement. The protection against the race condtion is done through sem_wait() and sem_post() of course.
Next we go through a infinite while loop that will check if connected == NUM_LINES/5. This checking is protected by the binary semaphore connected_lock. If connected == NUM_LINES, then we exit the
protected region and sleep for 1 second. We then check if NUM_LINES is greater than connected(before we do this we protect from race condition using sem_wait(connected_lock), meaning that there is an
open line for the caller. If the condition holds true, we increment connected and print "call ... is connected to an avaiable line, ring ring ring ... " . We then stop the protection of the
critcal region using sem_post(&connected_lock) and break out of the while loop using break. If the condition is not met, we end the critical region protection, and we do the loop over and over until
one of the lines is free. After this we beginning the operator print statements. These are protected with sem_wait(&operators) and sem_post(&operators) so that only two connected callers can be
connected with an operator. Next, we decrement connected(so that other callers can connect) and print the hang up print statement. These two actions being protected with the connected_lock semphore,
sem_wait(), and sem_post(). Lastly we detach the thread so that using pthread_detach(pthread_self()) to let the program know that we are done with this thread.    

TIMER FUCTION/THREAD: This function simply causes the program to sleep for a given amount of seconds and is the timer function. The program will run for (int time) seconds. So if you input 3, the
program with run for 3 seconds and int time variable will be equal to 3.

