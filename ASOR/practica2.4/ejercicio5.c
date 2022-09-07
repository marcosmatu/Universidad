#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	char buffer[256];
	int seleccion, tuberiaActual, numTuberiaActual;
	fd_set conjunto;
		
	int fd1 = open("tuberia", O_RDONLY | O_NONBLOCK);
	int fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);

	
	if(fd1 == -1 || fd2 == -1){
		perror("Error al abrir las tuberias");
		return -1;
	}
	
	while(seleccion != -1){
		FD_ZERO(&conjunto);
		FD_SET(fd1, &conjunto);
		FD_SET(fd2, &conjunto);
		
		seleccion = select((fd1 < fd2) ? fd2 + 1 : fd1 + 1, &conjunto, NULL, NULL, NULL);
		
		if(seleccion > 0){
			if(FD_ISSET(fd1, &conjunto)){
				numTuberiaActual = 1;
				tuberiaActual = fd1;
			}else if(FD_ISSET(fd2, &conjunto)){
				numTuberiaActual = 2;
				tuberiaActual = fd2;
			}
			
			ssize_t size = 256;
			while(size == 256){
				size = read(tuberiaActual, buffer, 256);
				buffer[size] = '\0';
				printf("Tuberia %i, Mensaje: %s", numTuberiaActual, buffer);
			}
			
			if(size != 256 && numTuberiaActual == 1){
				close(fd1);
				fd1 = open("tuberia", O_RDONLY | O_NONBLOCK);
                			if(fd1 == -1){
                   				perror("Error en la apertura de la tuberia");
                   				close(fd1);
                   				close(fd2);
                   				return -1;
                			}
			}else if(size != 256 && numTuberiaActual == 2){
               		close(fd2);
                		fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
                			if(fd2 == -1){
                    				perror("Error en la apertura de la tuberia2");
                    				close(fd1);
                   				close(fd2);
                   				return -1;
                			}
            		}
		}
	
	}
	close(fd1);
        close(fd2);
	return 0;
}
