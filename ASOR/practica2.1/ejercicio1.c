#include <stdio.h>
#include <unistd.h>

int main(){
	if(setuid(0) == -1){
		perror("Error setuid 2");
		return -1;
	}
	return 0;
}
