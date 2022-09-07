#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

int main(){
	time_t t = time(NULL);
	printf("Hora desde el Epoch en segundos: %ld\n", t);
	return 0;
}
