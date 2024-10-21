#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    // Here, we're creating the shared memory segment.
    int segment_id = shmget(IPC_PRIVATE, sizeof(int), S_IRUSR | S_IWUSR);

    // Initializing him.
    int *sharedMemory = (int *) shmat(segment_id, NULL, 0);

    *sharedMemory = 0;

    pid_t processoFilho1 = fork();
    if (processoFilho1 < 0) {
        printf("Sou o processo %d e não consegui criar um novo processo.\n", getpid());
        return 1;
    } else if (processoFilho1 == 0) {
        *sharedMemory = 10; // Appended memory.
        shmdt(sharedMemory);
        exit(0);
    }

    pid_t processoFilho2 = fork();
    if (processoFilho2 < 0) {
        printf("Sou o processo %d e não consegui criar um novo processo.\n", getpid());
        return 1;
    } else if (processoFilho2 == 0) {
        sharedMemory = (int *) shmat(segment_id, NULL, 0); // Appending memory to the second child.
        if (sharedMemory == (int *) -1) {
            perror("Erro ao anexar memória compartilhada no filho 2");
            exit(1);
        }
        *sharedMemory += 10;
        shmdt(sharedMemory);
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    sharedMemory = (int *) shmat(segment_id, NULL, 0);
    printf("Valor armazenado ao final: %d\n", *sharedMemory);
    shmctl(segment_id, IPC_RMID, NULL);

    return 0;
}
