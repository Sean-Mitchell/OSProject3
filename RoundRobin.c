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
*	My round robin implementation is bad.  I am not switching process' if there is left over time in time quantum when
*	a process finishes.  That means the processor utilization will be bad.
*/
void runRoundRobin()
{
	//must start at -1 due to while loop logic
	int index = -1;
	int timeTakenByProcesses = 0;
	int finishedProcesses = 0;
	int totalLatency = 0;
	int totalTurnaround = 0;
	
	double totalNormalizedturnaround = 0;
	double nonUtilizationTime = 0;
	double utilizationTime = 0;
	
	while (finishedProcesses != TOTAL_PROCESSES)
	{
		//turns the dynamic process into a queue
		index = (index + 1) % TOTAL_PROCESSES;
		
		//only does logic on unfinished processes
		if (dynamicProcess[index].timeArrive <= timeTakenByProcesses || dynamicProcess[index].timeLeft != 0)
		{
			//Increment latency counters first
			if (dynamicProcess[index].timeSinceLastRun == timeTakenByProcesses - 1)
			{
				dynamicProcess[index].timeSinceLastRun = timeTakenByProcesses;
			}
			else
			{
				dynamicProcess[index].totalTimeWaitingForCPU += timeTakenByProcesses - dynamicProcess[index].timeSinceLastRun;
				dynamicProcess[index].timeSinceLastRun = timeTakenByProcesses;
			}
			
			//Checks to see if there are any processor cycles not used and add them to the unutilized time
			if (dynamicProcess[index].timeLeft <= RR_TIME_QUANTUM)
			{				
				
				dynamicProcess[index].turnaround = timeTakenByProcesses + dynamicProcess[index].timeLeft - dynamicProcess[index].timeArrive;
				dynamicProcess[index].normalTurnaround = ((double)dynamicProcess[index].turnaround)/dynamicProcess[index].runTime;
				dynamicProcess[index].taskCompletionTime = timeTakenByProcesses + dynamicProcess[index].timeLeft;
				
				nonUtilizationTime += RR_TIME_QUANTUM - dynamicProcess[index].timeLeft;
				
				totalLatency += dynamicProcess[index].totalTimeWaitingForCPU;
				totalTurnaround += dynamicProcess[index].turnaround;
				totalNormalizedturnaround += dynamicProcess[index].normalTurnaround;
				
				
				dynamicProcess[index].timeLeft = 0;
				finishedProcesses++;
			}
			else
			{
				dynamicProcess[index].timeLeft = dynamicProcess[index].timeLeft - RR_TIME_QUANTUM;
			}
			timeTakenByProcesses += RR_TIME_QUANTUM;
		}
		
		
		printf("process %i finish time: %i\n", dynamicProcess[index].processId, timeTakenByProcesses);
		printf("process %i turnaround time: %i\n", dynamicProcess[index].processId, dynamicProcess[index].turnaround);
		printf("process %i normalized turnaround time: %f\n", dynamicProcess[index].processId, dynamicProcess[index].normalTurnaround);
		
	}
	
	if (nonUtilizationTime == 0)
	{
		utilizationTime = 1.0;
	}
	else
	{
		utilizationTime = (double)(timeTakenByProcesses - nonUtilizationTime)/timeTakenByProcesses;
	}
	
	//Prints off some of the general information
	printf("average turnaround time: %f\n", (double) totalTurnaround / TOTAL_PROCESSES);
	printf("average normalized turnaround time: %f\n", (double) totalNormalizedturnaround / TOTAL_PROCESSES);
	printf("average latency: %f\n", (double) totalLatency / TOTAL_PROCESSES);
	printf("processor utilization: %f\n", utilizationTime);
	printf("Round ROBin complete\n\n");
	
	printCSVFile("RoundRobin.csv", (double)totalTurnaround / TOTAL_PROCESSES, (double)totalNormalizedturnaround / TOTAL_PROCESSES,
				(double)totalLatency / TOTAL_PROCESSES, utilizationTime);
}

