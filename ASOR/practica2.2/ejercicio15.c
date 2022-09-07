#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char *argv[]){
	int fd;
	char hora[50];
	fd = open(argv[1],O_RDWR, 0666);
	if (fd == -1){
		return -1;
	}
	
	if((lockf(fd,F_TEST,0)) ==  0){
		printf("Proceso desbloqueado\n");
		lockf(fd,F_LOCK,0);
		time_t now = time(NULL);
		struct tm *tm_struct = localtime(&now);
		sprintf(hora, "%d:%d\n", tm_struct->tm_hour,tm_struct->tm_min);
		write(fd,hora,5);
		sleep(5);
		lockf(fd,F_ULOCK,0);
	}else{
		printf("Proceso bloqueado\n");
	}
	
	return 0;
}
