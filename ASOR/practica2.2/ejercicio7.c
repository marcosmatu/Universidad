#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	umask(026);
	int fich = open("ej7", O_CREAT,0540);
	if(fich == -1) return -1;
	close(fich);
	return 0;
}
