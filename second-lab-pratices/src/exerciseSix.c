#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>

/** NOTE:
 * Unlike "exerciseThree.c", we're not using shared memory resources.
 * And the question is: why not?
 * Let me break it for you: the communication between processes needs to make system calls (syscalls) to
 * share information, due to the principles of "Process Isolation" and "OS Security". These principles ensure that
 * each process operates in its own isolated memory space, which prevents unauthorized access and modifications
 * to the data of other processes. This design enhances the overall security of the operating system by controlling
 * the flow of information between processes, making the exchange more secure and reliable.
 * 
 * In contrast, threads are merely instances of the same process, meaning they share the same address space
 * and resources as the calling thread. Because of this shared context, threads can communicate and access
 * shared data directly without needing to make system calls. This reduces the overhead associated with communication
 * but introduces potential risks, such as race conditions if multiple threads attempt to modify shared data simultaneously.
 * Therefore, while using shared memory can facilitate efficient communication within a single process context,
 * the mechanisms that govern process communication must be in place to uphold the principles of isolation and security 
 * across different processes in a multi-process environment.
 */


// Global variables for the threads' acess.
int acc = 0;
int aux = 0;

// Functions that will be passed on to the threads.
void *incrementAccumulator(void *pointer){
	acc += aux;
	aux += 1;
	printf("Thread [%d] || Partial sum > %d\n", aux, acc);
	pthread_exit(NULL);
}

int main(int argc, char **argv){

	// Number of threads selection.
	int n = 0;
	printf("Insira um número > ");
	scanf("%d", &n);

	// Threads "array".
	pthread_t threads[n];
	
	for(int i = 0; i < n; i++){
		// Threads' creation and its function calling.
		pthread_create(&threads[i], NULL, incrementAccumulator, NULL);
	}

	for(int i = 0; i < n; i++){
		// Calling thread waiting the called threads to finish their operation.
		pthread_join(threads[i], NULL);
	}

	printf("The result is > %d", acc);

	return 0;
}