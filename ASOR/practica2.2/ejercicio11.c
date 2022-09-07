#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[]){
	struct stat buffer;

	if(stat(argv[1], &buffer) == -1) return -1;
	
	char* hard = malloc(strlen(argv[1]) + (sizeof(char) * 5));
	hard = strcpy(hard,argv[1]);
	hard = strcat(hard,".hard");
	
	char* sym = malloc(strlen(argv[1]) + (sizeof(char) * 4));	
	sym = strcpy(sym,argv[1]);
	sym = strcat(sym, ".sym");
	
	int type = buffer.st_mode & S_IFMT;
	if(type == S_IFREG) {
		link(argv[1],hard);
		symlink(argv[1],sym);
		
	}else return -1;

	free(hard);
	free(sym);
	
	return 0;
}
