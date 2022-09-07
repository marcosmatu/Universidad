#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <stdio.h>



int main(int argc, char *argv[]){
	struct stat buffer;

	if(lstat(argv[1], &buffer) == -1) return -1;
	printf("Major asociado al dispositivo: %d\n",major(buffer.st_dev));
	printf("Minor asociado al dispositivo: %d\n",minor(buffer.st_dev));
	printf("Numero inodo del fichero: %ld\n" , buffer.st_ino);
	int type = buffer.st_mode & S_IFMT;
	if(type == S_IFDIR) printf("Tipo de fichero: directorio\n");
	else if(type == S_IFREG) printf("Tipo de fichero: fichero ordinario\n");
	else printf("Tipo de fichero: enlace simbolico\n");
	
	printf("Ultima vez que se accedio al fichero: %ld\n",buffer.st_atime);
	return 0;
}
