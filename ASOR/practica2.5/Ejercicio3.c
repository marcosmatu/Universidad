
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char **argv){

    if(argc != 4){
        printf("Introducir como argumentos la dirección del servidor, el puerto y el comando a consultar\n");
        return -1;
    }
    struct addrinfo hints;
    hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;


    struct addrinfo *res;
    if(getaddrinfo(argv[1], argv[2], &hints, &res) == -1){
		perror("No se ha podido obtener la información\n");
        return -1;
    }

    int udp_socket = socket(res->ai_family, SOCK_DGRAM, res->ai_protocol);
    if(udp_socket == -1){
        perror("Error al crear el socket");
        return -1;
    }

    struct sockaddr_storage dest_addr;
    socklen_t addrlen = sizeof(dest_addr);

    
    if(sendto(udp_socket, argv[3], strlen(argv[3]), 0, res->ai_addr, res->ai_addrlen) == -1){
        perror("No se ha podido enviar el mensaje");
        return -1;
    }

    char buf_recv[256];
    ssize_t recv_size = recvfrom(udp_socket, buf_recv, 256, 0, res->ai_addr, &res->ai_addrlen);
    if(recv_size == -1){
        perror("No se ha podido recibir el mensaje");
        return -1;
    }

    buf_recv[recv_size] = '\0';

    printf("%s", buf_recv);

    return 0;
}