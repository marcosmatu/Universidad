#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/select.h>


int main(int argc, char *argv[]){
	if(argc != 3){
		perror("Introducir como argumentos la dirección del servidor y el puerto\n");
		return -1;
	}

    struct addrinfo hints;
    hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

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

    char command[2];
    struct sockaddr_storage storage;
    socklen_t storage_len = sizeof(storage);
	ssize_t size;

    fd_set set;

    do{    
        FD_ZERO(&set);
        FD_SET(0, &set);
        FD_SET(udp_sd, &set);
        int enviarCliente;

        int selection = select(udp_sd + 1, &set, NULL, NULL, NULL);
        if(selection == -1)
          perror("Error al hacer el select");
           
        if(FD_ISSET(0, &set)){
            ssize_t size = read(0, command, strlen(command));
            if(size == -1){
                perror("Error leyendo de teclado");
                return -1;
            }
            command[1] = '\0';
            enviarCliente = 0;
        }
        else if(FD_ISSET(udp_sd, &set)){
            int size = recvfrom(udp_sd, &command, sizeof(command), 0, (struct sockaddr *) &storage, &storage_len);
            if(size == -1){
                perror("Error leyendo por red");
                return -1;
            } 

            command[size - 1] = '\0';
            char host[NI_MAXHOST];
            char port[NI_MAXSERV];
            
            if(getnameinfo((struct sockaddr *) &storage, storage_len, host, NI_MAXHOST, port, NI_MAXSERV, 0) != 0){
                perror("No se ha podido obtener la direccion");
                return -1;
            }
            printf("%d bytes de %s:%s\n", size, host, port);
            enviarCliente = 1;
        }
        
        setlocale(LC_TIME, "");
        time_t t;
        struct tm *local;
        char buffer[256];

        time(&t);
        struct tm *lt = localtime(&t);    
        switch(command[0]){
			case 't':
				strftime(buffer, 256, "%H:%M:%S\n", lt);
                if(enviarCliente){
                    size = sendto(udp_sd, buffer, strlen(buffer), 0, (struct sockaddr *) &storage, storage_len);
                    if(size == -1){
                        perror("No se ha podidio enviar la hora");
                        return -1;
                    }
                }else{
                    printf("%s", buffer);
                }
				break;

			case 'd':
				strftime(buffer, 256, "%d/%m/%Y\n", lt);
                if(enviarCliente){
                    size = sendto(udp_sd, buffer, strlen(buffer), 0, (struct sockaddr *) &storage, storage_len);
                    if(size == -1){
                        perror("No se ha podido enviar la fecha");
                        return -1;
                    }
                }else{
                    printf("%s", buffer);
                }
				break;

            case 'q':
                printf("Saliendo...\n");

			//default: printf("Comando %c no soportado\n", command[0]);
		}
    }while(command[0] != 'q');

	return 0;
}
