#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ejer8(pid_t pid_fork, char *cmd, int argc, char *argv[]){
	char *arg[argc-1];
	
	for(int i = 0; i < argc; i++) arg[i] = argv[i+1];
	
	if(execvp(cmd,arg) == -1) return -1;
	
	printf("El comando terminó de ejecutarse\n");

	return 0;
}

int main(int argc, char *argv[]){
	pid_t pid;	
	pid = fork();
	
	if(argc < 2){ printf("Es necesario un argumento\n");return -1;}
	
	switch (pid){
		case -1:
			perror("fork");
			exit(1);
			
		case 0:
			if(setsid() == -1) return -1;
			
			printf("Hijo\n");
			
			int in,out,err;
			if((in = open("/dev/null",O_WRONLY | O_CREAT)) == -1 || (out = open("/tmp/daemon.out",O_WRONLY | O_CREAT)) == -1 || (err = open("/tmp/daemon.err",O_WRONLY | O_CREAT))==-1) return -1;
			
			if(dup2(in,0) == -1 || dup2(out,1) == -1 || dup2(err,2) == -1) return -1;
			
			ejer8(pid, argv[1], argc, argv);
			
			close(in);
			close(out);
			close(err);
			
			break;
			
		default:
			printf("Padre\n");
			break;
		
	}
	
	return 0;
}
