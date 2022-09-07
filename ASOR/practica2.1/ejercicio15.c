#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <locale.h>
#include <sys/time.h>



int main(){
	time_t t = time(NULL);
	struct tm *time = localtime(&t);
	
	char buff[50];
	setlocale(LC_ALL,"es_ES");
	strftime(buff,50,"%A, %d de %B de %Y, %H:%M",time);
	printf("%s\n", buff);	
	return 0;
} 
