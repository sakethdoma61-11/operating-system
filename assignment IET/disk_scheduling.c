#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int absValue(int x) {
    return x < 0 ? -x : x;
}

/* FCFS */
void FCFS(int request[], int n, int head) {

    int total = 0;
    int current = head;

    printf("\n========== FCFS ==========\n");
    printf("Order: %d ", head);

    for (int i = 0; i < n; i++) {

        total += absValue(current - request[i]);

        current = request[i];

        printf("-> %d ", current);
    }

    printf("\nTotal Head Movement = %d cylinders\n", total);
}

/* SSTF */
void SSTF(int request[], int n, int head) {

    int visited[MAX] = {0};

    int total = 0;
    int current = head;

    printf("\n========== SSTF ==========\n");
    printf("Order: %d ", head);

    for (int count = 0; count < n; count++) {

        int index = -1;
        int minimum = 999999;

        for (int i = 0; i < n; i++) {

            if (!visited[i]) {

                int distance =
                    absValue(current - request[i]);

                if (distance < minimum) {

                    minimum = distance;
                    index = i;
                }
            }
        }

        visited[index] = 1;

        total += minimum;

        current = request[index];

        printf("-> %d ", current);
    }

    printf("\nTotal Head Movement = %d cylinders\n", total);
}

/* SCAN */
void SCAN(int request[], int n, int head, int diskSize) {

    int total = 0;
    int current = head;

    int left[MAX], right[MAX];

    int l = 0, r = 0;

    for (int i = 0; i < n; i++) {

        if (request[i] < head)
            left[l++] = request[i];
        else
            right[r++] = request[i];
    }

    /* Sort left side */
    for (int i = 0; i < l - 1; i++) {

        for (int j = i + 1; j < l; j++) {

            if (left[i] > left[j]) {

                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }
        }
    }

    /* Sort right side */
    for (int i = 0; i < r - 1; i++) {

        for (int j = i + 1; j < r; j++) {

            if (right[i] > right[j]) {

                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }
        }
    }

    printf("\n========== SCAN ==========\n");
    printf("Order: %d ", head);

    /* Move right */
    for (int i = 0; i < r; i++) {

        total += absValue(current - right[i]);

        current = right[i];

        printf("-> %d ", current);
    }

    /* Go to end */
    if (current != diskSize - 1) {

        total += absValue(current - (diskSize - 1));

        current = diskSize - 1;

        printf("-> %d ", current);
    }

    /* Reverse and service left */
    for (int i = l - 1; i >= 0; i--) {

        total += absValue(current - left[i]);

        current = left[i];

        printf("-> %d ", current);
    }

    printf("\nTotal Head Movement = %d cylinders\n", total);
}

/* C-SCAN */
void CSCAN(int request[], int n, int head, int diskSize) {

    int total = 0;
    int current = head;

    int left[MAX], right[MAX];

    int l = 0, r = 0;

    for (int i = 0; i < n; i++) {

        if (request[i] < head)
            left[l++] = request[i];
        else
            right[r++] = request[i];
    }

    /* Sort left */
    for (int i = 0; i < l - 1; i++) {

        for (int j = i + 1; j < l; j++) {

            if (left[i] > left[j]) {

                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }
        }
    }

    /* Sort right */
    for (int i = 0; i < r - 1; i++) {

        for (int j = i + 1; j < r; j++) {

            if (right[i] > right[j]) {

                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }
        }
    }

    printf("\n========== C-SCAN ==========\n");
    printf("Order: %d ", head);

    /* Move right */
    for (int i = 0; i < r; i++) {

        total += absValue(current - right[i]);

        current = right[i];

        printf("-> %d ", current);
    }

    /* Go to end */
    total += absValue(current - (diskSize - 1));

    current = diskSize - 1;

    printf("-> %d ", current);

    /* Jump to beginning */
    total += diskSize - 1;

    current = 0;

    printf("-> %d ", current);

    /* Service left side */
    for (int i = 0; i < l; i++) {

        total += absValue(current - left[i]);

        current = left[i];

        printf("-> %d ", current);
    }

    printf("\nTotal Head Movement = %d cylinders\n", total);
}

int main() {

    int request[MAX];

    int n;
    int head;
    int diskSize;

    printf("============================================\n");
    printf(" MULTIPLAYER GAME SERVER\n");
    printf(" DISK SCHEDULING SIMULATOR\n");
    printf("============================================\n");

    printf("\nEnter number of requests: ");
    scanf("%d", &n);

    printf("Enter disk request queue:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &request[i]);

    printf("\nEnter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &diskSize);

    FCFS(request, n, head);

    SSTF(request, n, head);

    SCAN(request, n, head, diskSize);

    CSCAN(request, n, head, diskSize);

    printf("\n============================================\n");
    printf(" SIMULATION COMPLETED\n");
    printf("============================================\n");

    return 0;
}
