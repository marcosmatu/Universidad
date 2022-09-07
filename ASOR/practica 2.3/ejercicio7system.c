#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	if(system(argv[1]) == -1) return -1;
	printf("El comando terminó de ejecutarse\n");
	return 0;
}
