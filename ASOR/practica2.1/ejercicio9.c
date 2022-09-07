#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>

int main(){
	printf("Real: %d\n", getuid());
	printf("Efectivo: %d\n", geteuid());
	return 0;
}
//Si el getuid y el geteuid devuelven un valor distinto signica que esta activado.
