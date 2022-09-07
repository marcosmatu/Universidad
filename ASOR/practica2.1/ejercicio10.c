#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <sys/types.h>

int main(){
	printf("Real: %d\n", getuid());
	printf("Efectivo: %d\n", geteuid());
	
	struct passwd *p = getpwuid(getuid());
	printf("Nombre de usuario: %s\n", p->pw_name);
	printf("Directorio home: %s\n", p->pw_dir);
	printf("Descripción del usuario: %s\n", p->pw_gecos);
	
	return 0;
}
