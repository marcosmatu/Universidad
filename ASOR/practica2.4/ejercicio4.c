#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	
	if(argc != 2){
		printf("Introducir solo un argumento\n");
		return -1;
	}
	
	int fd = open("tuberia",O_WRONLY);
	if(fd == -1) return -1;
	
	if(write(fd, argv[1], strlen(argv[1])) == -1) return -1;
	close(fd);
	return 0;
}
