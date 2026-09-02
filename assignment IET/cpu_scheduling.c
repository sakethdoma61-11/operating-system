#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct {
    int pid;
    int arrival;
    int burst;
    int priority;
    int completion;
    int turnaround;
    int waiting;
    int remaining;
} Process;

/* ---------- FCFS ---------- */
void fcfs(Process p[], int n) {
    int time = 0;

    printf("\n========== FCFS SCHEDULING ==========\n");
    printf("Gantt Chart:\n");

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;

        printf("| P%d ", p[i].pid);

        time += p[i].burst;
        p[i].completion = time;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }

    printf("|\n");

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);

        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);
}

/* ---------- SJF Non-Preemptive ---------- */
void sjf(Process p[], int n) {
    int completed[MAX] = {0};
    int count = 0;
    int time = 0;

    printf("\n========== SJF (NON-PREEMPTIVE) ==========\n");
    printf("Gantt Chart:\n");

    while (count < n) {
        int index = -1;
        int shortest = 9999;

        for (int i = 0; i < n; i++) {
            if (!completed[i] &&
                p[i].arrival <= time &&
                p[i].burst < shortest) {

                shortest = p[i].burst;
                index = i;
            }
        }

        if (index == -1) {
            time++;
            continue;
        }

        printf("| P%d ", p[index].pid);

        time += p[index].burst;

        p[index].completion = time;
        p[index].turnaround =
            p[index].completion - p[index].arrival;
        p[index].waiting =
            p[index].turnaround - p[index].burst;

        completed[index] = 1;
        count++;
    }

    printf("|\n");

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);

        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);
}

/* ---------- Priority Non-Preemptive ---------- */
void priorityScheduling(Process p[], int n) {
    int completed[MAX] = {0};
    int count = 0;
    int time = 0;

    printf("\n========== PRIORITY SCHEDULING ==========\n");
    printf("Priority 1 = Highest Priority\n");
    printf("Gantt Chart:\n");

    while (count < n) {
        int index = -1;
        int bestPriority = 9999;

        for (int i = 0; i < n; i++) {
            if (!completed[i] &&
                p[i].arrival <= time &&
                p[i].priority < bestPriority) {

                bestPriority = p[i].priority;
                index = i;
            }
        }

        if (index == -1) {
            time++;
            continue;
        }

        printf("| P%d ", p[index].pid);

        time += p[index].burst;

        p[index].completion = time;
        p[index].turnaround =
            p[index].completion - p[index].arrival;
        p[index].waiting =
            p[index].turnaround - p[index].burst;

        completed[index] = 1;
        count++;
    }

    printf("|\n");

    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].priority,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);

        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);
}

/* ---------- Round Robin ---------- */
void roundRobin(Process p[], int n, int quantum) {
    int queue[MAX * 20];
    int front = 0, rear = 0;

    int visited[MAX] = {0};
    int time = 0;
    int completed = 0;

    for (int i = 0; i < n; i++)
        p[i].remaining = p[i].burst;

    printf("\n========== ROUND ROBIN ==========\n");
    printf("Time Quantum = %d\n", quantum);
    printf("Gantt Chart:\n");

    /* Start with the first process */
    int first = 0;

    while (first < n && p[first].arrival > time)
        time++;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && p[i].arrival <= time) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n) {

        if (front == rear) {
            time++;

            for (int i = 0; i < n; i++) {
                if (!visited[i] && p[i].arrival <= time) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }

            continue;
        }

        int index = queue[front++];

        int executionTime;

        if (p[index].remaining < quantum)
            executionTime = p[index].remaining;
        else
            executionTime = quantum;

        printf("| P%d ", p[index].pid);

        time += executionTime;
        p[index].remaining -= executionTime;

        /* Add newly arrived processes */
        for (int i = 0; i < n; i++) {
            if (!visited[i] && p[i].arrival <= time) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (p[index].remaining > 0) {
            queue[rear++] = index;
        } else {
            p[index].completion = time;

            p[index].turnaround =
                p[index].completion - p[index].arrival;

            p[index].waiting =
                p[index].turnaround - p[index].burst;

            completed++;
        }
    }

    printf("|\n");

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);

        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    printf("\nAverage Waiting Time = %.2f\n",
           totalWT / n);

    printf("Average Turnaround Time = %.2f\n",
           totalTAT / n);
}

/* ---------- Copy Process Data ---------- */
void copyProcesses(Process source[], Process destination[], int n) {
    for (int i = 0; i < n; i++) {
        destination[i] = source[i];
    }
}

/* ---------- Main ---------- */
int main() {

    int n;
    int quantum;

    Process original[MAX];

    printf("============================================\n");
    printf(" MULTIPLAYER GAME SERVER\n");
    printf(" CPU SCHEDULING SIMULATOR\n");
    printf("============================================\n");

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid number of processes.\n");
        return 0;
    }

    printf("\nEnter Process Details\n");
    printf("(Arrival Time, Burst Time, Priority)\n\n");

    for (int i = 0; i < n; i++) {

        original[i].pid = i + 1;

        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &original[i].arrival);

        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &original[i].burst);

        printf("P%d Priority: ", i + 1);
        scanf("%d", &original[i].priority);

        original[i].completion = 0;
        original[i].turnaround = 0;
        original[i].waiting = 0;
        original[i].remaining = original[i].burst;
    }

    printf("\nEnter Round Robin Time Quantum: ");
    scanf("%d", &quantum);

    if (quantum <= 0) {
        printf("Invalid time quantum.\n");
        return 0;
    }

    Process p1[MAX];
    Process p2[MAX];
    Process p3[MAX];
    Process p4[MAX];

    copyProcesses(original, p1, n);
    copyProcesses(original, p2, n);
    copyProcesses(original, p3, n);
    copyProcesses(original, p4, n);

    fcfs(p1, n);

    sjf(p2, n);

    priorityScheduling(p3, n);

    roundRobin(p4, n, quantum);

    printf("\n============================================\n");
    printf(" CPU SCHEDULING SIMULATION COMPLETED\n");
    printf("============================================\n");

    return 0;
}


