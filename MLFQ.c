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
*	I ran out of time to implement run MLFQ
*	How I wanted to do it was take the process array, and put all it's indecies into the topmost queue.
*	I would then pass in a variable of how long the time quantum is into a function that does math that emulates the process doing work.
*	After all this was done, once the time quantum was up I would take the id, remove it from the topmost queue, and add it to the second queue.
*	Then while processes are in the first queue, that queue's processes do work, otherwise the next highest.
*	After all processes are done I would do math similar to the other scheduling algorithms.
*/
void runMLFQ()
{
	//must start at -1 due to while loop logic
	/*int index = -1;
	int timeTakenByProcesses = 0;
	int totalLatency = 0;
	int totalTurnaround = 0;
	int oldClockTime = 0;
	
	
	double totalNormalizedturnaround = 0;
	double nonUtilizationTime = 0;
	double utilizationTime = 0;*/
	
	int finishedProcesses = 0;
	int SCountdown = MLFQ_S;
	int firstFront = -1, 
	firstRear = -1;
	/*secondFront = -1, 
	secondRear = -1,
	thirdFront = -1, 
	thirdRear = -1, 
	fourthFront = -1, 
	fourthRear = -1;*/
	
	
	while (finishedProcesses != TOTAL_PROCESSES)
	{
		//population of highest priority queue with indecies of the processes
		int i = 0;
		firstFront = i; 
		firstRear = i;
		/*secondFront = i; 
		secondRear = -i; 
		thirdFront = i; 
		thirdRear = i; 
		fourthFront = i; 
		fourthRear = i;*/
		
		int tempValue = 0;
		for (i = 0; i < TOTAL_PROCESSES; i++)
		{
			enQueue(firstRear, firstFront, firstMLFQ, i);
		}
		
		while (SCountdown != 0)
		{
			if (firstRear - firstFront != 0)
			{
				if (dynamicProcess[firstMLFQ[firstFront]].timeLeft == 0)
				{
					deQueue(firstRear, firstFront, firstMLFQ);
				}
				else
				{
					tempValue = firstMLFQ[firstFront];
					deQueue(firstRear, firstFront, firstMLFQ);
					enQueue(firstRear, firstFront, firstMLFQ, tempValue);					
				}
			}
			
		}
	}
	
}


/*
*	Queueing functions for MLFQ
*	Taken from: http://btechsmartclass.com/DS/U2_T8.html
*/
void enQueue(int rear, int front, int queue[], int value)
{
   if(rear == TOTAL_PROCESSES-1)
      printf("\nQueue is Full!!! Insertion is not possible!!!");
   else{
      if(front == -1)
	 front = 0;
      rear++;
      queue[rear] = value;
   }
}
void deQueue(int rear, int front, int queue[])
{
   if(front == rear)
      printf("\nQueue is Empty!!! Deletion is not possible!!!");
   else{
      front++;
      if(front == rear)
	 front = rear = -1;
   }
}
