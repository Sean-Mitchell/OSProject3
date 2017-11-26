#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "ProcessStruc.h"
#include "MethodHeaders.h"

int RR_TIME_QUANTUM = 0;
int MLFQ_S = 0;
int TOTAL_PROCESSES = 0;
Process * dynamicProcess = NULL;

/*
*	Queue variables
*/
int firstMLFQ[0],
	secondMLFQ[0],
	thirdMLFQ[0],
	fourthMLFQ[0]; 
	
/*
*	Main Program
*/
int main(int argc, char *argv[]) 
{
	
	//Create File Pointer for input
	FILE *inputfp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
	int count = 0;
	char *temp;
	inputfp = fopen(argv[1], "rb");

	
	if (!inputfp)
	{
		printf("Unable to open file.\n");
		return -1;
	}	
	
	while ((read = getline(&line, &len, inputfp)) != -1) {
		if (TOTAL_PROCESSES == 0)
		{
			TOTAL_PROCESSES = atoi(line);
			dynamicProcess = (Process *) malloc(sizeof(Process) * TOTAL_PROCESSES);
		}
		else if (count < TOTAL_PROCESSES)
		{

			dynamicProcess[count].processId = count;
			temp = strtok(line, ",");
			dynamicProcess[count].timeArrive = atoi(temp);
			
			temp = strtok(NULL, ",");
			dynamicProcess[count].runTime = atoi(temp);
			dynamicProcess[count].timeLeft = atoi(temp);
			count++;
		}
		else if (count == TOTAL_PROCESSES)
		{
			temp = strtok(line, ",");
			RR_TIME_QUANTUM = atoi(temp);
		}
		else
		{			
			temp = strtok(line, ",");
			MLFQ_S = atoi(temp);
		}
    }
	
    fclose(inputfp);
    if (line)
        free(line);
	
	//	Statically create actual run guys
	runFIFOOnMyCoolArray();
	
	//Print everything in a csv before resetting	
	resetObjectValues();
	
	//Run SJF
	runShortestJobFirst();
	
	
	//Print everything in a csv before resetting	
	resetObjectValues();
	
	
	runRoundRobin();
	//Print everything in a csv before clearing out memory
	
	free(dynamicProcess);
	
	/*
	*	Must Reset all values other than processId, timeArrive, and runTime to 0
	*	This must happen between every scheduling algorithm
	*/
	
	printf("We did it Reddit\n");
	
	
	
	return 0;
}