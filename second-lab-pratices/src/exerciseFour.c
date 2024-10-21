#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Global variables of the threads number.
int numberOfThreads = 5;

// Global variables for the threads' acess.
pthread_cond_t cond;
int threadFinished = 0;

// Functions that will be passed on to the threads.
void *printHello(void *tid) {
    printf("Olá, eu sou a thread %d\n", (int)(size_t) tid);
    
    // "Whoa, I finished!"
    threadFinished = 1;
    // "Tell boss that I'm finished."
    pthread_cond_signal(&cond);

    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    pthread_t threads[numberOfThreads];

    pthread_cond_init(&cond, NULL);

    for (int i = 0; i < numberOfThreads; i++) {
        // Threads' creation and its function calling.
        int status = pthread_create(&threads[i], NULL, printHello, (void *)(size_t) i);
        
        // Wait the called thread.
        while (threadFinished == 0) {
            pthread_cond_wait(&cond, NULL);
        }
        // Make it clean to the next thread.
        threadFinished = 0;
    }

    // "Free".
    pthread_cond_destroy(&cond);

    return 0;
}
