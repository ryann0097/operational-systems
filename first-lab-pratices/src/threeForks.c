#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char **argv){
fork();
fork();
fork();
printf("bodia, eu sou o processo de ID > %d\n",getpid());
return 0;
}
