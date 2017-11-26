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
*	This runs the shortest job first scheduling algorithm.
*
*/
void runShortestJobFirst()
{
	int shortestJobIndex = 0;
	int timeTakenByProcesses = 0;
	int finishedProcesses = 0;
	int totalLatency = 0;
	int totalTurnaround = 0;
	int oldClockTime = 0;
	
	double totalNormalizedturnaround = 0;
	double nonUtilizationTime = 0;
	double utilizationTime = 0;
	
	
	while (finishedProcesses != TOTAL_PROCESSES)
	{
	
		//First Sort and take the job that runs the shortest amount whose arrival time
		//Must run at the start to make sure you take the smallest 
		//Gets index of shortest running job
		shortestJobIndex = getShortestJobIndex(timeTakenByProcesses);
		
		//checks to see if there is a job that is available after time has passed
		//EG the next shortest time process is after a few more clock cycles
		if (shortestJobIndex == -1)
		{		
			oldClockTime = timeTakenByProcesses;
			timeTakenByProcesses = advanceClockCycles(timeTakenByProcesses);
			nonUtilizationTime += timeTakenByProcesses - oldClockTime;
			shortestJobIndex = getShortestJobIndex(timeTakenByProcesses);
		}
		
		//Increments time taken
		dynamicProcess[shortestJobIndex].timeLeft--;
		timeTakenByProcesses++;

		//marks a time so latency can be calculated for process
		//IF the time is off by one do not add any to processes latency country
		// else add time between last run and current time
		if (dynamicProcess[shortestJobIndex].timeSinceLastRun == timeTakenByProcesses - 1)
		{
			dynamicProcess[shortestJobIndex].timeSinceLastRun = timeTakenByProcesses;
		}
		else
		{
			totalLatency++;
			dynamicProcess[shortestJobIndex].totalTimeWaitingForCPU += timeTakenByProcesses - dynamicProcess[shortestJobIndex].timeSinceLastRun;
			dynamicProcess[shortestJobIndex].timeSinceLastRun = timeTakenByProcesses;
		}
			
		if (dynamicProcess[shortestJobIndex].timeLeft == 0)
		{
			finishedProcesses++;
			dynamicProcess[shortestJobIndex].taskCompletionTime = timeTakenByProcesses;
			dynamicProcess[shortestJobIndex].turnaround = timeTakenByProcesses - dynamicProcess[shortestJobIndex].timeArrive;
			dynamicProcess[shortestJobIndex].normalTurnaround = ((double)dynamicProcess[shortestJobIndex].turnaround)/dynamicProcess[shortestJobIndex].runTime;
			totalTurnaround += dynamicProcess[shortestJobIndex].turnaround;
			totalNormalizedturnaround += dynamicProcess[shortestJobIndex].normalTurnaround;
		}
		printf("process %i finish time: %i\n", dynamicProcess[shortestJobIndex].processId, timeTakenByProcesses);
		printf("process %i turnaround time: %i\n", dynamicProcess[shortestJobIndex].processId, dynamicProcess[shortestJobIndex].turnaround);
		printf("process %i normalized turnaround time: %f\n", dynamicProcess[shortestJobIndex].processId, dynamicProcess[shortestJobIndex].normalTurnaround);
		
	}
	
	//Also do normalized/ turnaround sum here similar to FIFO
	//Include Utilization here
	//Checks to see if there was any time spent by the processor not working
	//	(true)
	//		makes the processor utilization 100%
	//	(false)
	//		figures out the time spent used in the processor
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
	printf("SJF complete\n\n");

	printCSVFile("ShortestJobFirst.csv", (double)totalTurnaround / TOTAL_PROCESSES, (double)totalNormalizedturnaround / TOTAL_PROCESSES,
				(double)totalLatency / TOTAL_PROCESSES, utilizationTime);
}


/*
*	Gets the index of the next shortest job
*/
int getShortestJobIndex(int timePassed) 
{
	int smallestTime = 999999999;
	int smallestTimeIndex = -1;
	int i = 0;
	for (i = 0; i < TOTAL_PROCESSES; i++)
	{
		if (dynamicProcess[i].timeArrive <= timePassed && dynamicProcess[i].timeLeft < smallestTime
			&& dynamicProcess[i].timeLeft != 0)
		{
			smallestTimeIndex = i;
			smallestTime = dynamicProcess[i].timeLeft;
		}
	}
	
	return smallestTimeIndex;
}

//Returns what the clock cylcle should be if there is a delay between processes starting/utilization
int advanceClockCycles(int timePassed)
{
	int timeReturn = 99999999;
	
	int i = 0;
	for (i = 0; i < TOTAL_PROCESSES; i++)
	{
		if (dynamicProcess[i].timeArrive >= timePassed && dynamicProcess[i].timeLeft < timeReturn
			&& dynamicProcess[i].timeLeft != 0)
		{
			timeReturn = dynamicProcess[i].timeLeft;
		}
	}
	
	return timeReturn;
}

