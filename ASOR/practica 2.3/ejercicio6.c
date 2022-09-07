#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int print_atributos(pid_t pid_fork){

	pid_t pid,ppid,pgid,sid;
	struct rlimit rlim;
	char buffer[5000];
	
	pid = getpid();
	ppid = getppid();
	if((pgid = getpgid(pid)) == -1 || (sid = getsid(pid)) == -1) return -1;
	
	if(pid_fork == 0)
		if(chdir("/tmp") == -1) return -1;
	else sid = setsid();	
	
	printf("PID: %d, PPID: %d, PGPID: %d, SID: %d\n",pid,ppid,pgid,sid);
	
	if(getrlimit(RLIMIT_NOFILE, &rlim) == -1) return -1;
	printf("Número máximo de ficheros que puede abrir el proceso: %ld\n",rlim.rlim_max);
	
	if(getcwd(buffer, sizeof(buffer)) == NULL ) return -1;
	printf("Directorio de trabajo: %s\n", buffer);
	
	return 0;
}


int main(){
	pid_t pid;
	
	pid = fork();
	
	switch (pid){
		case -1:
			perror("fork");
			exit(1);
		case 0:
			printf("Hijo\n");
			print_atributos(pid);
			break;
		default:
			sleep(5);
			printf("Padre\n");
			print_atributos(pid);
			break;
		
	}
	
	return 0;
}
