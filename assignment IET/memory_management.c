#include <stdio.h>

#define MAX 100

void FIFO(int pages[], int n, int frames) {

    int memory[MAX];
    int pointer = 0;
    int faults = 0;

    for (int i = 0; i < frames; i++)
        memory[i] = -1;

    for (int i = 0; i < n; i++) {

        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (memory[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {

            memory[pointer] = pages[i];

            pointer = (pointer + 1) % frames;

            faults++;
        }
    }

    printf("FIFO Page Faults = %d\n", faults);
}

void LRU(int pages[], int n, int frames) {

    int memory[MAX];
    int recent[MAX];

    int faults = 0;

    for (int i = 0; i < frames; i++) {
        memory[i] = -1;
        recent[i] = 0;
    }

    for (int i = 0; i < n; i++) {

        int found = -1;

        for (int j = 0; j < frames; j++) {

            if (memory[j] == pages[i]) {
                found = j;
                break;
            }
        }

        if (found != -1) {

            recent[found] = i;

        } else {

            int position = -1;

            for (int j = 0; j < frames; j++) {
                if (memory[j] == -1) {
                    position = j;
                    break;
                }
            }

            if (position == -1) {

                int least = recent[0];
                position = 0;

                for (int j = 1; j < frames; j++) {

                    if (recent[j] < least) {
                        least = recent[j];
                        position = j;
                    }
                }
            }

            memory[position] = pages[i];
            recent[position] = i;

            faults++;
        }
    }

    printf("LRU Page Faults = %d\n", faults);
}

int findOptimal(int pages[], int n, int current,
                int memory[], int frames) {

    int farthest = current;
    int position = -1;

    for (int i = 0; i < frames; i++) {

        int j;

        for (j = current; j < n; j++) {

            if (memory[i] == pages[j]) {

                if (j > farthest) {
                    farthest = j;
                    position = i;
                }

                break;
            }
        }

        if (j == n)
            return i;
    }

    if (position == -1)
        return 0;

    return position;
}

void Optimal(int pages[], int n, int frames) {

    int memory[MAX];
    int faults = 0;

    for (int i = 0; i < frames; i++)
        memory[i] = -1;

    for (int i = 0; i < n; i++) {

        int found = 0;

        for (int j = 0; j < frames; j++) {

            if (memory[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {

            int position = -1;

            for (int j = 0; j < frames; j++) {

                if (memory[j] == -1) {
                    position = j;
                    break;
                }
            }

            if (position == -1)
                position = findOptimal(pages, n, i + 1,
                                       memory, frames);

            memory[position] = pages[i];

            faults++;
        }
    }

    printf("Optimal Page Faults = %d\n", faults);
}

int main() {

    int pages[MAX];
    int n, frames;

    printf("============================================\n");
    printf(" MULTIPLAYER GAME SERVER\n");
    printf(" MEMORY MANAGEMENT SIMULATOR\n");
    printf("============================================\n");

    printf("\nEnter number of page references: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("\nEnter number of frames: ");
    scanf("%d", &frames);

    printf("\n========== PAGE REPLACEMENT RESULTS ==========\n");

    FIFO(pages, n, frames);
    LRU(pages, n, frames);
    Optimal(pages, n, frames);

    printf("\n============================================\n");
    printf(" SIMULATION COMPLETED\n");
    printf("============================================\n");

    return 0;
}
