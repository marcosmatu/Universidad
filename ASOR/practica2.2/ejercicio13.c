#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
	int fd;
	fd = open(argv[1],O_RDWR, 0666);
	if (fd == -1){
		return -1;
	}
	if(dup2(fd,STDOUT_FILENO) == -1) return -1;
	
	if(dup2(fd,STDERR_FILENO) == -1) return -1;
	
	int i;
	for(i = 0; i < 10; i++){
		printf("Esta es una prueba de la salida estandar\n");
	}
	
	fprintf(stderr, "Esta es una prueba de la salida estandar de error\n");
	
	if(close(fd) == -1) return -1;
	
	return 0;
}
