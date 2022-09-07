#include <unistd.h>
#include <stdio.h>
#include <sys/resource.h>

int main(int argc, char *argv[]){

	pid_t pid,ppid,pgid,sid;
	struct rlimit rlim;
	char buffer[5000];
	
	pid = getpid();
	ppid = getppid();
	if((pgid = getpgid(pid)) == -1 || (sid = getsid(pid)) == -1) return -1;
	
	printf("PID: %d, PPID: %d, PGPID: %d, SID: %d\n",pid,ppid,pgid,sid);
	
	if(getrlimit(RLIMIT_NOFILE, &rlim) == -1) return -1;
	printf("Número máximo de ficheros que puede abrir el proceso: %ld\n",rlim.rlim_max);
	
	if(getcwd(buffer, sizeof(buffer)) == NULL ) return -1;
	printf("Directorio de trabajo: %s\n", buffer);
	
	return 0;
}

