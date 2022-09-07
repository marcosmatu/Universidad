#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int fd[2];
	pid_t pid;
	
	if(argc != 5){
		printf("Introduce los 4 argumetnos");
		return -1;
	}
	
	if(pipe(fd) == -1){
		perror("tuberia");
		return -1;
	}
	
	pid = fork();
	
	switch(pid){
		case -1:
			perror("fork");
			return -1;
			break;
		
		case 0:
			close(0);
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			if(execlp(argv[3], argv[3], argv[4], (char *)NULL) == -1) return -1;
			return 0;
			break;
			
		default:
			close(1);
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			if(execlp(argv[1], argv[1], argv[2],(char *)NULL) == -1) return -1;
			return 0;
			break;
		
	}	
	return 0;
}
