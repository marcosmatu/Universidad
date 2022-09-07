#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fich = open("ej5", O_CREAT,0645);
	if(fich == -1) return -1;
	close(fich);
	return 0;
}
