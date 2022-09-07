#include <stdio.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	int polPlanificacion = sched_getscheduler(0);
	struct sched_param param;
	
	if(polPlanificacion == -1) return -1;
	else{
		switch(polPlanificacion){
			case SCHED_OTHER:
					printf("Esta siendo usado el planificador estandar\n");
					break;
			case SCHED_FIFO:
					printf("Esta siendo usado el planificador fifo\n");
					break;
			case SCHED_RR:
					printf("Esta siendo usado el planificador round robin\n");
		}
		if(sched_getparam(0, &param) == -1) return -1;
		else{
			printf("Prioridad: %d\n", param.sched_priority);
			
			int max = sched_get_priority_max(polPlanificacion);
			int min = sched_get_priority_min(polPlanificacion);
		
			if(max == -1 || min == -1) return -1;
			else printf("Minimo: %d, Maximo: %d\n",min,max);
		}
	}
	return 0;
}
