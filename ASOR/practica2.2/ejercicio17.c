#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Error: el programa debe incluir como argumento la ruta a un directorio");
		return -1;
	}

	DIR *dr = opendir(argv[1]);
	if(dr == NULL){
		perror("Error al abrir el directorio");
		return -1;
	} 
	struct stat buffer;
	int type;
	float sum = 0;
	char nameSymbolic[50];
	char b[50];
	struct dirent *dir = readdir(dr);
	while(dir != NULL){
		sprintf(b,"%s/%s",argv[1],dir->d_name);
		if(lstat(b, &buffer) == -1) return -1;
		type = buffer.st_mode & S_IFMT;
		if(type == S_IFDIR) printf("/%s\n",dir->d_name);
		else if(type == S_IFREG){
			if(buffer.st_mode & S_IXUSR) printf("%s*\n", dir->d_name);
			else printf("%s\n", dir->d_name);
			sum = sum + buffer.st_size;
		}
		else{
			readlink(b,nameSymbolic,50); 
			printf("%s->%s\n",dir->d_name,nameSymbolic);
			sum = sum + buffer.st_size;
		}
		dir = readdir(dr);
	
	}
	printf("Tamaño total que ocupan los ficheros: %f\n",sum/1000);
	closedir(dr);
	return 0;
}
