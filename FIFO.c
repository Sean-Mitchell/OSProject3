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
*	This procedure runs the first in first out scheduling algorithm.
*/
void runFIFOOnMyCoolArray() 
{
	
	printf("Hello, I'm FIFO and I'm starting timing now!\n");
	
	//	Localtime variables from start, total time taken for this run, processorUtilization, totalLatency, 
	//	summation of turnaround times
	int timeTakenByProcesses = 0;
	int processorTimeNotUtilized = 0;
	int totalFIFOLatency = 0;	
	int FIFOTurnaroundSum = 0;
	int FIFONormalTurnaroundSum = 0;
	
	double utilizationTime = 0;
	
	//Counter variable
	int i;
	
	for (i = 0; i < TOTAL_PROCESSES; i++) 
	{
		
		//	Check to see if the process has arrived yet, if it hasn't,
		//		(true) 
		//			Then the utilization of the processor is 0 for that amount of time 
		//			and time is incremented up to the next elements start time.
		//		(false)
		//			The process that is about to start has a latency amount that must be added to it
		//			Also adds to the total latency for the entire FIFO runtime
		if (timeTakenByProcesses < dynamicProcess[i].timeArrive) 
		{
			
			timeTakenByProcesses = dynamicProcess[i].timeArrive;
			processorTimeNotUtilized += dynamicProcess[i].timeArrive - timeTakenByProcesses;
		}
		else if (timeTakenByProcesses > dynamicProcess[i].timeArrive)
		{
			dynamicProcess[i].totalTimeWaitingForCPU = timeTakenByProcesses - dynamicProcess[i].timeArrive;
			totalFIFOLatency += timeTakenByProcesses - dynamicProcess[i].timeArrive; 
		}
		
		//	Processes runtime added to time run
		timeTakenByProcesses += dynamicProcess[i].runTime;
		
		//	Compute Turnarounds for individual process		
		dynamicProcess[i].taskCompletionTime = timeTakenByProcesses;
		dynamicProcess[i].turnaround = timeTakenByProcesses-dynamicProcess[i].timeArrive;
		dynamicProcess[i].normalTurnaround = ((double)dynamicProcess[i].turnaround) / dynamicProcess[i].runTime;
		
		//	Compute sum of FIFO turnaround
		FIFOTurnaroundSum += dynamicProcess[i].turnaround;
		FIFONormalTurnaroundSum += dynamicProcess[i].normalTurnaround;
		
		printf("process %i finish time: %i\n", dynamicProcess[i].processId, timeTakenByProcesses);
		printf("process %i turnaround time: %i\n", dynamicProcess[i].processId, dynamicProcess[i].turnaround);
		printf("process %i normalized turnaround time: %f\n", dynamicProcess[i].processId, dynamicProcess[i].normalTurnaround);
		
	}
	
	
	//Checks to see if there was any time spent by the processor not working
	//	(true)
	//		makes the processor utilization 100%
	//	(false)
	//		figures out the time spent used in the processor
	if (processorTimeNotUtilized == 0)
	{
		utilizationTime = 1.0;
	}
	else
	{
		utilizationTime = (double)(timeTakenByProcesses - processorTimeNotUtilized)/timeTakenByProcesses;
	}
	
	
	//Prints off some of the general information
	printf("average turnaround time: %f\n", (double)FIFOTurnaroundSum/TOTAL_PROCESSES);
	printf("average normalized turnaround time: %f\n", (double)FIFONormalTurnaroundSum/TOTAL_PROCESSES);
	printf("average latency: %f\n", (double)totalFIFOLatency/TOTAL_PROCESSES);
	printf("processor utilization: %f\n", utilizationTime);
	printf("FIFO complete\n\n");
	
	printCSVFile("FIFO.csv", ((double)FIFOTurnaroundSum) / TOTAL_PROCESSES, ((double)FIFONormalTurnaroundSum) / TOTAL_PROCESSES,
				((double)totalFIFOLatency)/TOTAL_PROCESSES, utilizationTime);
	
}
