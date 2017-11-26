#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "ProcessStruc.h"
#include "MethodHeaders.h"

int RR_TIME_QUANTUM;
int MLFQ_S;
int TOTAL_PROCESSES;
Process * dynamicProcess;

/*
*	Queue variables
*/
int firstMLFQ[0],
	secondMLFQ[0],
	thirdMLFQ[0],
	fourthMLFQ[0]; 
/*
*	After a scheduling algorithm is run the processes need to have their internal info resetObjectValues
*	This method does that for all processes in the array
*/
void resetObjectValues() 
{
	int i;
	
	for (i = 0; i < TOTAL_PROCESSES; i++) 
	{ 
		dynamicProcess[i].taskCompletionTime = 0;  
		dynamicProcess[i].totalTimeWaitingForCPU = 0;  
		dynamicProcess[i].timeSinceLastRun = dynamicProcess[i].timeArrive; 
		dynamicProcess[i].turnaround = 0;  
		dynamicProcess[i].normalTurnaround = 0; 
		dynamicProcess[i].timeLeft = dynamicProcess[i].runTime; 
	}
}

/*
*	Prints out the csv file for the specific scheduling algorithm
*/
void printCSVFile(char* fileName, double aveTurnaroundTime, double aveNormalizedTurnaroundTime, double aveLatency, double utilization)
{
	int i = 0;
	FILE *outputfp;
	
	outputfp = fopen(fileName, "w+");
	if (!outputfp)
	{
		printf("Unable to open file.\n");
	}	
	
	fprintf(outputfp,"ProcessId,Finish Time,Turnaround Time,Normalized Turnaround Time\n");
	
	for (i = 0; i < TOTAL_PROCESSES; i++)
	{
		fprintf(outputfp,"%d,%d,%d,%.2f\n", dynamicProcess[i].processId, dynamicProcess[i].taskCompletionTime, dynamicProcess[i].turnaround, dynamicProcess[i].normalTurnaround);	
	}
	
	fprintf(outputfp,"\nAverage Turnaround Time: %.2f\n", aveTurnaroundTime);	
	fprintf(outputfp,"\nAverage Normalized Turnaround Time: %.2f\n", aveNormalizedTurnaroundTime);	
	fprintf(outputfp,"\nAverage Latency: %.2f\n", aveLatency);	
	fprintf(outputfp,"\nProcessor Utilization: %.2f\n", utilization);	
	fclose(outputfp);
}