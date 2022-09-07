#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

bool borrar = true;

void handler(int signal){
	if(signal == SIGUSR1) borrar = false;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		printf("Introduce como argumento solo el número de segundos que va a tardar en borrarse el ejecutable\n");
		return -1;
	}
	
	sigset_t blk;
	
	if(sigemptyset(&blk) == -1) return -1; 
	if(sigaddset(&blk, SIGUSR1) == -1) return -1;
	if(sigprocmask(SIG_UNBLOCK, &blk, NULL) == -1) return -1;
	
	struct sigaction action;
	if(sigaction(SIGUSR1, NULL, &action) == -1) return -1;
	action.sa_handler = handler;
	if(sigaction(SIGUSR1, &action, NULL) == -1) return -1;
	
	int segundos = atoi(argv[1]);
	
	int i = 0;
	while( i < segundos && borrar){
		i = i + 1;
		sleep(1);
	}
	
	if(borrar){
		printf("El ejecutable se va a eliminar\n");
		unlink(argv[0]);
	}else{
		printf("El ejecutable no se eliminara\n");
	}
	
	return 0;
}
