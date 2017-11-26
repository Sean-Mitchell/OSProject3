void fifo(process *processList, int numProcesses)
{
	int i, time = 0, turnaround, turnaroundSum = 0, unusedTime = 0, latencySum = 0;
	double nturnaround, nTurnaroundSum = 0.0, utilization;
	
	printf("FIFO:\n");
	
	for (i = 0; i < numProcesses; i++)
	{
		if (time < processList[i].arrivalTime)
		{
			unusedTime += processList[i].arrivalTime - time;
			time = processList[i].arrivalTime;
		}
		else if (time > processList[i].arrivalTime)
		{
			latencySum += time - processList[i].arrivalTime;
		}
		
		time += processList[i].burstTime;
		
		turnaround = time-processList[i].arrivalTime;
		nturnaround = (double)turnaround/processList[i].burstTime;
		
		turnaroundSum += turnaround;
		nTurnaroundSum += nturnaround;
		
		printf("process %i finish time: %i\n", i, time);
		printf("process %i turnaround time: %i\n", i, turnaround);
		printf("process %i normalized turnaround time: %f\n", i, nturnaround);
	}
	
	if (unusedTime > 0)
	{
		utilization = (double)(time - unusedTime)/time;
	}
	else
	{
		utilization = 1.0;
	}
	
	printf("average turnaround time: %f\n", (double)turnaroundSum/i);
	printf("average normalized turnaround time: %f\n", (double)nTurnaroundSum/i);
	printf("average latency: %f\n", (double)latencySum/i);
	printf("processor utilization: %f\n", utilization);
	printf("FIFO complete\n\n");
}