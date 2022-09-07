#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){

	if(argc != 3){
		perror("Introducir como argumentos la dirección del servidor y el puerto\n");
		return -1;
	}

	struct addrinfo *res;
	if(getaddrinfo(argv[1], argv[2], NULL, &res) != 0){
		perror("No se ha podido obtener la información\n");
		return -1;	
	}

	int udp_sd = socket(res->ai_family, SOCK_DGRAM, 0);

    if(udp_sd == -1){
        perror("Error no se ha podido crear el socket UDP");
        return -1;
    }
    
    if(bind(udp_sd, res->ai_addr, res->ai_addrlen) == -1){
        perror("No se ha podido hacer bind");
        return -1;
    }

    char command;
    struct sockaddr_storage storage;
    socklen_t storage_len = sizeof(storage);
	int size;

	

	while(command != 'q'){
        pid_t pid = fork();
        
        switch(pid){
            case -1:
                perror("Error fork");
                return -1;
                break;
            
            case 0:
         	    size = recvfrom(udp_sd, &command, sizeof(char), 0, (struct sockaddr *) &storage, &storage_len);

                if(size == -1){
                    perror("Error leyendo del cliente");
                    return -1;
                }   
                char host[NI_MAXHOST];
                char port[NI_MAXSERV];

                if(getnameinfo((struct sockaddr *) &storage, storage_len, host, NI_MAXHOST, port, NI_MAXSERV, 0) != 0){
                    perror("Error obteniendo direccion");
                    return -1;
                }

                printf("%d bytes de %s:%s PID: %d\n", size, host, port, getpid());

                setlocale(LC_TIME, "");
                time_t t;
                struct tm *local;
                char buffer[256];

                time(&t);
                struct tm *lt = localtime(&t);
                switch(command){
                    case 't':
                        strftime(buffer, 256, "%H:%M:%S\n", lt);
                        size = sendto(udp_sd, buffer, strlen(buffer), 0, (struct sockaddr *) &storage, storage_len);
                        if(size == -1){
                            perror("No se ha podidio enviar la hora");
                            return -1;
                        }
                        break;

                    case 'd':
                        strftime(buffer, 256, "%d/%m/%Y\n", lt);
                        size = sendto(udp_sd, buffer, strlen(buffer), 0, (struct sockaddr *) &storage, storage_len);
                        if(size == -1){
                            perror("No se ha podido enviar la fecha");
                            return -1;
                        }
                        break;
                    case 'q':
                        printf("Saliendo...\n");
                        break;

                    default: printf("Comando %c no soportado\n", command);
                }              
            break;

            default:
                wait(NULL);
                break;
        }
	}

	return 0;
}
