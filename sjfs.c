#include <stdio.h>

struct Process
{
    int processID;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int isCompleted;
};

void calculateWaitingTime(struct Process processes[], int n)
{
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n)
    {
        int shortestJobIndex = -1;
        int shortestBurstTime = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && !processes[i].isCompleted)
            {
                if (processes[i].burstTime < shortestBurstTime)
                {
                    shortestBurstTime = processes[i].burstTime;
                    shortestJobIndex = i;
                }
            }
        }

        if (shortestJobIndex == -1)
        {
            currentTime++;
            continue;
        }

        processes[shortestJobIndex].waitingTime = currentTime - processes[shortestJobIndex].arrivalTime;
        currentTime += processes[shortestJobIndex].burstTime;
        processes[shortestJobIndex].turnaroundTime = processes[shortestJobIndex].waitingTime + processes[shortestJobIndex].burstTime;
        processes[shortestJobIndex].isCompleted = 1;
        completedProcesses++;
    }
}

void calculateTurnaroundTime(struct Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void calculateAverageTimes(struct Process processes[], int n)
{
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++)
    {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    double avgWaitingTime = (double)totalWaitingTime / n;
    double avgTurnaroundTime = (double)totalTurnaroundTime / n;

    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

void displayProcessTable(struct Process processes[], int n)
{
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++)
    {
        printf("Process %d\n", i + 1);
        processes[i].processID = i + 1;
        printf("Enter Arrival Time: ");
        scanf("%d", &process
