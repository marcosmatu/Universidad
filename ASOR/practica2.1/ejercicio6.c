#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>

int main(){
	long int arg,hij,fichero;
	if((arg = sysconf(_SC_ARG_MAX)) == -1 || (hij = sysconf(_SC_CHILD_MAX)) == -1 || (fichero = sysconf(_SC_OPEN_MAX)) == -1) return -1;
	printf("Longitud máxima de los argumentos: %ld\n", arg);
	printf("Número máximo de hijos: %ld\n", hij);
	printf("Número máximo de ficheros: %ld\n", fichero);
	return 0;
}
