#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

int main(){
	time_t t = time(NULL);
	struct tm *time = localtime(&t);
	printf("Estamos en el año: %d\n",time->tm_year + 1900);
	return 0;
} 
