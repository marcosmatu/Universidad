#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char *argv[]){

	if(argc != 2){
		perror("Introducir solo un host como argumento\n");
		return -1;
	}
	
	struct addrinfo *res, *next;
	
	if(getaddrinfo(argv[1], NULL, NULL, &res) != 0){
		perror("No se ha podido obtener la información\n");
		return -1;
	}
	
	next = res;
	while(next != NULL){
	
		char host[NI_MAXHOST];
		if(getnameinfo(next->ai_addr, next->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST) != 0){
			perror("No se ha podido obtener la información\n");
			return -1;			
		}
		printf("Host: %s\tFamilia: %i\tSocket: %i\n", host, next->ai_family, next->ai_socktype);
		next = next->ai_next;
	}
	
	return 0;
}
