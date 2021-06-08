//include statements 
#include <stdio.h>
#include <pthread.h> 
#include <stdlib.h>
#include <semaphore.h> 
#include <unistd.h>
//global variables and prototypes 
volatile next_id = 1; //the global variable for phone call ID, this variable will have to be protected 
static sem_t connected_lock; //semaphore for connected(binary)
static sem_t operators; // The operators counting semaphore is used once a call connects with an operator
static sem_t idLock; //semaphore created for nextID variable (binary)
static int NUM_OPERATORS = 2; //total number of operators 
static int NUM_LINES = 5; //total number of lines
static int connected = 0;    // Callers that are connected, access to connected must be controlled by a critical, and is done by using the connected_lock binary semaphore
void *phonecall(void *vargp);  //prototype for phonecall function/thread


void *timer(void *vargp); //prototype for timer function/thread

//The main function runs the program. First I create an array of pthreads_t that has a size of 200. This array will hold all the phonecall threads. Then I decare an int called debateTime and initialize it
//to the command line input given to the program. atoi() function takes the input and converts it to a useable int value. Then I create the thread that will be for the timer function, this being timerID.
//Next I initalize all the semaphores using sem_init. The semaphore for idLock and connected_lock are are both binary semaphores therefore their last argument of sem_init() is 1,
//meaning only one thread can access a critical region at a time giving these two semaphores. The last argument for sem_init() in regards to operators semaphore is 2/ NUM_OPERATORS, because we are
//allowed to have two threads access a critical region for this semaphore. After initalizing the semaphores, the program creates the 200 phonecall threads using a loop that
//goes 200 times, and creates a new thread/phonecall within each loop using pthread_create(). The TID of each of these threads is stored in the calls[] pthread array(first argument of the
//pthread_create()),
//and the thread being executed is of course phonecall (the third argument of the pthread_create()) since
//we need to create 200 phonecalls. Once we do this, we create the timer thread that causes the main thread to wait a certain amount of time, which is given by a command line input(&debateTime/fourth
//argument of this pthread_create()). We create this timer
//thread with pthread_create(), and the TID of the timer thread is held witin timerID variable(first argument of this pthread_create()). Since this thread created is supposed to run the timer function,
//we pass in timer as the second argument of this pthread_create(). After creating this thread, we tell the main thread to wait until the timer thread is finished, this is done with pthread_join(). Since
//we are waiting for the timer thread to finish, timerID is passed into the first argument of pthread_join since this variable holds the ID of our timer thread. Then we destroy all the semaphores we
//created by using the sem_destroy() function, and passing in the semaphore variable names as the arguuments of the sem_destroy() calls to tell the program which semaphores to kill. And finally, we kill the
//program as well as all the phonecall threads by making a call to exit(0).
int main(int argc, char *argv[]){
	pthread_t calls[200]; //array that will hold all the TIDs of the phonecalls
	int debateTime = atoi(argv[1]); //int variable that will hold the command line input for number of seconds to sleep within timer function
	pthread_t timerID; //thread for timer
	sem_init(&operators,0,NUM_OPERATORS); //initalizing operators semaphore
	sem_init(&connected_lock,0,1); //initalizing connected_lock semaphore
	sem_init(&idLock,0,1); //initalizing idLock semaphore

	for(int i = 0; i < 200; i++){ //for loop that will create all the phonecall threads
		pthread_create(&calls[i],NULL,phonecall,NULL); //creating the phonecalls
	}
	
	pthread_create(&timerID,NULL,timer, &debateTime); //sleeping timer thread
	pthread_join(timerID,NULL); //wait for timer thread to be done
	sem_destroy(&operators); //we now destroy all thg semaphores
	sem_destroy(&connected_lock);
	sem_destroy(&idLock);
	
	exit(0); //kill program and all phonecall threads

	
}
//This is the function for the phone call thread. First we create a local int variable called callerID that will hold a value between 1-200, the 1-200 comes from next_id global variable. We next
//increment next_id so that no two threads will have the same callerID. The program then prints that this thread "is attempting to connect...". All of this is done within the binary sempaphore idLock, so
//that a race condition will not occur for the incrementing and assigning of next_id and the print statement. The protection against the race condtion is done through sem_wait() and sem_post() of course.
//Next we go through a infinite while loop that will check if connected == NUM_LINES/5. This checking is protected by the binary semaphore connected_lock. If connected == NUM_LINES, then we exit the
//protected region and sleep for 1 second. We then check if NUM_LINES is greater than connected(before we do this we protect from race condition using sem_wait(connected_lock), meaning that there is an
//open line for the caller. If the condition holds true, we increment connected and print "call ... is connected to an avaiable line, ring ring ring ... " . We then stop the protection of the
//critcal region using sem_post(&connected_lock) and break out of the while loop using break. If the condition is not met, we end the critical region protection, and we do the loop over and over until
//one of the lines is free. After this we beginning the operator print statements. These are protected with sem_wait(&operators) and sem_post(&operators) so that only two connected callers can be
//connected with an operator. Next, we decrement connected(so that other callers can connect) and print the hang up print statement. These two actions being protected with the connected_lock semphore,
//sem_wait(), and sem_post(). Lastly we detach the thread so that using pthread_detach(pthread_self()) to let the program know that we are done with this thread. 																					
void *phonecall(void *vargp){
	sem_wait(&idLock); //protection of critical region
	int callerID = next_id; //assign local variable to a value between 1-200
	next_id++; //increment global variable
	printf("call %d is attempting to connect ... \n",callerID); 
	sem_post(&idLock); //end protection
	
	while(1){ //time to check for available line
		
		sem_wait(&connected_lock); //start protection of critical region
		if(connected == NUM_LINES){ //checks if all lines are full
        	}	
        	sem_post(&connected_lock); //end protection
        	sleep(1);	// if all lines busy then sleep one second
		
		sem_wait(&connected_lock);	//start protection of critical region
		if(NUM_LINES > connected){ //check again if all lines are busy
			connected++; //if not then a free line is now busy 
			printf("call %d is connected to an available line,ring ring ring...  \n", callerID);
			sem_post(&connected_lock); // end protection
			break;	//we dont need to check for available line anymore so break from loop
		}
		sem_post(&connected_lock); //end protection if if-statement does not go through 
	}

	sem_wait(&operators); //start protection of critical region
	printf("call %d is speaking to an operator. \n ", callerID);
	sleep(1); //sleep 1 second 
	printf("call %d has proposed a question for canditdates! The operator has left... \n",callerID);
	sem_post(&operators); //end protection
	
	sem_wait(&connected_lock); //start protection of critical region
	connected--; //a line is now free 
	printf("call %d has hung up! \n",callerID);
	sem_post(&connected_lock); //emd protection

	pthread_detach(pthread_self()); //this thread is no longer needed so detach
}
//This function simply causes the program to sleep for a given amount of seconds and is the timer function. The program will run as long for int time seconds. So if you iput 3, the program with run for 3
//seconds and int time will be equal to 3.
void *timer(void *vargp){
	int time = *((int*) (vargp)); //local variable that holds the command line value that was passed into pthread_create() for this timer thread
	sleep(time); //sleep for the time entered into command line
}
