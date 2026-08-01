#include "parta.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("ERROR: Missing arguments\n");
        return 1;
    }

     int *bursts;
    int count;
    int quantum = 0;

    if (strcmp(argv[1], "fcfs") == 0) {

        if (argc < 3) {
            printf("ERROR: Missing arguments\n");
            return 1;
        }

        printf("Using FCFS\n\n");

        count = argc - 2;
        bursts = malloc(sizeof(int) * count);

        for (int i = 0; i < count; i++) {
            bursts[i] = atoi(argv[i + 2]);
            printf("Accepted P%d: Burst %d\n", i, bursts[i]);
        }

        struct pcb *procs = init_procs(bursts, count);

        fcfs_run(procs, count);

        double total = 0;
        for (int i = 0; i < count; i++)
            total += procs[i].wait;

        printf("Average wait time: %.2f\n", total / count);

        free(procs);
        free(bursts);
    }

     else if (strcmp(argv[1], "rr") == 0) {

        if (argc < 4) {
            printf("ERROR: Missing arguments\n");
            return 1;
        }

        quantum = atoi(argv[2]);

        printf("Using RR(%d)\n\n", quantum);

        count = argc - 3;
        bursts = malloc(sizeof(int) * count);

        for (int i = 0; i < count; i++) {
            bursts[i] = atoi(argv[i + 3]);
            printf("Accepted P%d: Burst %d\n", i, bursts[i]);
        }

        struct pcb *procs = init_procs(bursts, count);

        rr_run(procs, count, quantum);

        double total = 0;

        for (int i = 0; i < count; i++)
            total += procs[i].wait;

        printf("Average wait time: %.2f\n", total / count);

        free(procs);
        free(bursts);
    }

     else {
        printf("ERROR: Missing arguments\n");
        return 1;
    }

    return 0;

}
