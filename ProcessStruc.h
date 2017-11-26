typedef struct process{
	
	//ProcessId, comes from iterating over the processes
	int processId;
	
	//What you read in from the file
	int timeArrive;
	int runTime;
	
	//used for turnaround time
	int timeLeft;
	int taskCompletionTime;		//This is for turnaroundTime end time
	
	//Timing mechanism for MLFQ to see how much time is left in that queues time
	int timeLeftInQueue;
	
	//used to compute latency
	int totalTimeWaitingForCPU;	
	int timeSinceLastRun;
	
	//Turnaround/ NormalizedTurnaround
	int turnaround;
	double normalTurnaround;
	
	
} Process;