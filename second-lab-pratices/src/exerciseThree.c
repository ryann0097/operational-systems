#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char **argv){

	int n = 0;
	printf("Insert a number > ");
	scanf("%d", &n);
	
	// Shared memory segment creation.
	int segment_id = shmget(IPC_PRIVATE, sizeof(int), S_IRUSR|S_IWUSR);
	
	// Initializing shared memory segment for the father-process.
	int *sharedMemory = (int *) shmat(segment_id, NULL, 0);

	/** NOTE:
	 * Why are we appending the memory to the father process?
 	 * So, in the model that we're using, the father process is the one who creates and manages the
 	 * shared memory segment. Like the base-knowing of father-child processes, we know that the son
 	 * has access to the same memory segment as the father. However, each child process must 
 	 * explicitly attach this shared memory to its own address space in order to modify it.
 	 * The father process doesn't directly serve as a backup for the data but rather acts as the 
 	 * central manager of the shared resource, ensuring that all child processes can access the same 
 	 * shared memory for communication.
 	 */

	// Initializing sharedMemory value.
	*sharedMemory = 0;

	int i;

	// Loop to create the child processes and make the operations.
	for(i = 0; i < n; i++){
		pid_t pid = fork();

		if(pid == 0){ // Child process.
			// Appending the memory to the child process.
			sharedMemory = (int *) shmat(segment_id, NULL, 0);
			
			*sharedMemory += i;
			printf("Process [%d] | Partial sum > %d\n", i+1, *sharedMemory);

			shmdt(sharedMemory);
			exit(0);
		} else if (pid > 0){
			wait(NULL);
		}
	}

	printf("The result is > %d", *sharedMemory);

	shmdt(sharedMemory);
	shmctl(segment_id, IPC_RMID, NULL);

	return 0;
}