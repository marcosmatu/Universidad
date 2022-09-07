#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

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
    connect(tcp_sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

    char buff_cli[256];
    char buff_serv[256];

    ssize_t c;
    while(1){
        c = read(0, buff_cli, 255);
        buff_cli[c] = '\0';

        if(buff_cli[0] == 'q' && c == 2){
            return 0;
        }

        if(send(tcp_sd, buff_cli, c, 0) == -1){
            perror("Error al enviar el mensaje");
            return -1;
        }

        c = recv(tcp_sd, buff_serv, 255, 0);
        buff_serv[c] = '\0';
        printf("%s", buff_serv);
    }

    return 0;
}