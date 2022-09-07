#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	
	int fd_p_h[2];
	int fd_h_p[2];
	pid_t pid;
	int fin = 0, m = 0;
	char buffer[256];

	
	if(pipe(fd_p_h) == -1 || pipe(fd_h_p) == -1){
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
			close(fd_p_h[1]);
			close(fd_h_p[0]);
			while(!fin){
				int rc = read(fd_p_h[0], buffer, 256);
				buffer[rc] = '\0';
				printf("Mensaje recibido: %s\n", buffer);
				sleep(1);
				if(++m == 10){
					write(fd_h_p[1], "q", 1);
					fin = 1;
				}else{
					write(fd_h_p[1], "l", 1);
				}
			}
			
			close(fd_p_h[0]);
			close(fd_h_p[1]);
			return 0;			
			break;
			
		default:
			close(fd_p_h[0]);
			close(fd_h_p[1]);
			
			while(!fin){
				printf("Introduce el mensaje: \n");
				scanf("%s", buffer);
				write(fd_p_h[1], buffer, strlen(buffer) +1);
				read(fd_h_p[0], buffer, 1);
				if(buffer[0] == 'q'){
					fin = 1;
				}
			
			}
			
			close(fd_p_h[1]);
			close(fd_h_p[0]);
			return 0;
			break;
	
	}
	
	return 0;
}
