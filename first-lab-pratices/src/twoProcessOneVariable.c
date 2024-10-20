#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int valor = 100;
int main(int agrc, char **agrv){
	pid_t pid = fork();
	if(pid == 0){
		valor+=100;
		exit(0);
	}
	else if(pid>0){
		wait(NULL);
	}
	printf("Valor da variável é %d\n", valor);
	return 0;
}
