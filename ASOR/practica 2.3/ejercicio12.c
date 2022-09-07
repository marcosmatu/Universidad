#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int cont_SIGINT = 0;
int cont_SIGTSTP = 0;

void handler(int signal){
	if(signal == SIGINT) cont_SIGINT++;
	if(signal == SIGTSTP) cont_SIGTSTP++;
}

int main(){
	sigset_t blk_set;
	struct sigaction action;
	
	if(sigaction(SIGINT, NULL, &action) == -1) return -1;
	action.sa_handler = handler;
	if(sigaction(SIGINT, &action, NULL) == -1) return -1;
	
	if(sigaction(SIGTSTP, NULL, &action) == -1) return -1;
	action.sa_handler = handler;
	if(sigaction(SIGTSTP, &action, NULL) == -1) return -1;
	
	sigemptyset(&blk_set);
	while(cont_SIGINT + cont_SIGTSTP < 10){
		sigsuspend(&blk_set);
	}
	
	printf("\nSeñales del tipo SIGINT: %d\n", cont_SIGINT);
	printf("Señales del tipo SIGTSTP: %d\n", cont_SIGTSTP);
	
	return 0;
}
