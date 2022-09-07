#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>

int main(){
	struct utsname buffer;
	if(uname(&buffer)==-1){
		printf("Error %d: %s\n", errno, strerror(errno));
		return -1;
	}
	printf("sysname: %s\n", buffer.sysname);
	printf("nodename: %s\n", buffer.nodename);
	printf("release: %s\n", buffer.release);
	printf("version: %s\n", buffer.version);
	printf("machine: %s\n", buffer.machine);
	printf("domain name: %s\n", buffer.__domainname);
	/*
	#ifdef _GNU_SOURCE
		printf("domain name: %s\n", buffer.domainname);
	#endif
	*/
	return 0;
}
