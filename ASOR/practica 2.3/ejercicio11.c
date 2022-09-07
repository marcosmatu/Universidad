#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(){
	sigset_t blk_set, pending_set;

	if(sigemptyset(&blk_set) == -1 || sigaddset(&blk_set, SIGINT) == -1 || sigaddset(&blk_set,SIGTSTP) == -1) return -1;
	
	sigprocmask(SIG_BLOCK, &blk_set, NULL);
	
	char *sleep_time = getenv("SLEEP_SECS");
	int time = atoi(sleep_time);
	printf("El proceso se va a dormir %d segundos\n", time);
	sleep(time);
	
	if(sigpending(&pending_set) == -1) return -1;
	
	if(sigismember(&pending_set, SIGINT)) printf("Señal de SIGINT\n");
	
	if(sigismember(&pending_set, SIGTSTP)){
		printf("Señal de SIGTSTP\n");
		sigdelset(&blk_set, SIGTSTP);
	}
	
	sigprocmask(SIG_UNBLOCK, &blk_set, NULL);
	
	
	return 0;
}
