#include <stdio.h>

struct Process {
    int pid;       // Process ID
    int burstTime; // CPU Burst Time
};

void findWaitingTime(struct Process proc[], int n, int waitingTime[]) {
    waitingTime[0] = 0; // Waiting time for first process is 0

    for (int i = 1; i < n; i++) {
        waitingTime[i] = proc[i - 1].burstTime + waitingTime[i - 1];
    }
}

void findTurnAroundTime(struct Process proc[], int n, int waitingTime[], int turnAroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnAroundTime[i] = proc[i].burstTime + waitingTime[i];
    }
}

void findAverageTime(struct Process proc[], int n) {
    int waitingTime[n], turnAroundTime[n], totalWaitingTime = 0, totalTurnAroundTime = 0;

    findWaitingTime(proc, n, waitingTime);
    findTurnAroundTime(proc, n, waitingTime, turnAroundTime);

    printf("Processes   Burst time   Waiting time   Turn around time\n");

    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];
        printf("   %d ", proc[i].pid);
        printf("          %d ", proc[i].burstTime);
        printf("             %d", waitingTime[i]);
        printf("                %d\n", turnAroundTime[i]);
    }

    printf("Average waiting time = %.2f\n", (float)totalWaitingTime / (float)n);
    printf("Average turn around time = %.2f\n", (float)totalTurnAroundTime / (float)n);
}

int main() {
    struct Process proc[] = { {1, 10}, {2, 5}, {3, 8} };
    int n = sizeof(proc) / sizeof(proc[0]);

    findAverageTime(proc, n);

    return 0;
}
