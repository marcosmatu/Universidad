#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>

int main(){
	long int en,rut,nom;
	if((en = pathconf("/", _PC_LINK_MAX)) == -1 || (rut = pathconf("/",_PC_PATH_MAX)) == -1 || (nom = pathconf("/",_PC_NAME_MAX)) == -1) return -1;
	printf("Número máximo de enlaces: %ld\n", en);
	printf("Tamaño máximo de una ruta: %ld\n", rut);
	printf("Tamaño máximo de un nombre de fichero: %ld\n", nom);
	return 0;
}
