#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char **argv){
	pid_t pid = fork();
	if(pid < 0){
		printf("Sou o processo %d e não consegui criar um novo processo.\n", getpid());
		return 1;
	} else if (pid == 0){
		printf("Eun sou o processo filho e meu pai é o %d\n", getpid());
	} else {
		wait(NULL);
		printf("Eu sou o processo pai do %d e meu pid é %d.\n", pid, getpid());
	}
	return 0;
}