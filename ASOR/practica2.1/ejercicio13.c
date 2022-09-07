#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

int main(){
	struct timeval t1, t2;
	gettimeofday(&t1,NULL);
	
	int cont = 0;
	for(int i = 0; i < 1000000;i++){
		cont++;
	}
	
	gettimeofday(&t2,NULL);
	printf("Microsegundos que tarda en incrementar un millón de veces una variable: %ld\n", t2.tv_usec - t1.tv_usec);
	return 0;
}
