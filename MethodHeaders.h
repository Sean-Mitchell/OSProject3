//Method Headers
void runFIFOOnMyCoolArray();
void runShortestJobFirst();
void resetObjectValues();
int getShortestJobIndex();
int advanceClockCycles(int timePassed);
void runRoundRobin();
void runMLFQ();
void enQueue(int rear, int front, int queue[], int value);
void deQueue(int rear, int front, int queue[]);
void bringActiveProcessToFirstMLFQ();
void printCSVFile(char* fileName, double aveTurnaroundTime, double aveNormalizedTurnaroundTime, double aveLatency, double utilization);