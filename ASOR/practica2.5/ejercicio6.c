#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char **argv){

    if(argc != 3){
        printf("Introducir como argumentos la dirección del servidor y el puerto\n");
        return -1;
    }

    struct addrinfo *res, hints;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if(getaddrinfo(argv[1], argv[2], &hints, &res) != 0){
        perror("No se ha podido obtener la información\n");
        return -1;
    }

    int tcp_sd = socket(res->ai_family, res->ai_socktype, 0); 

    if(tcp_sd == -1){
        perror("Error no se ha podido crear el socket TCP");
        return -1;
    }

    if(bind(tcp_sd, res->ai_addr, res->ai_addrlen) == -1){
        perror("No se ha podido hacer bind");
        return -1;
    }
    
    freeaddrinfo(res);

    if(listen(tcp_sd, 5) == -1){
        perror("No se ha podido hacer listen");
        return -1;
    }

    char buff[256];
    ssize_t c;
    
    while(1){

        char host[NI_MAXHOST];
        char port[NI_MAXSERV];
        struct sockaddr_storage cliente;
        socklen_t clienteLen = sizeof(cliente);

        int cli_sd = accept(tcp_sd, (struct sockaddr *) &cliente, &clienteLen);
        if(cli_sd == -1){
            perror("Error aceptando");
            return -1;
        }
        if(getnameinfo((struct sockaddr *) &cliente, clienteLen, host, NI_MAXHOST, port, NI_MAXSERV, 0) != 0){
            perror("Error obteniendo direccion");
            return -1;
        } 

        printf("Conexion desde %s\t%s\n", host, port);

        while(c = recv(cli_sd, buff, 256, 0)){
            buff[c] = '\0';
            send(cli_sd, buff, c, 0);
        }
        printf("Conexión terminada\n");
    }

    
    return 0;
}