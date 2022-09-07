#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	char *cmd = argv[1];
	char *arg[argc-1];
	
	for(int i = 0; i < argc; i++) arg[i] = argv[i+1];
	
	if(execvp(cmd,arg) == -1) return -1;
	
	printf("El comando terminó de ejecutarse\n");

	return 0;
}
