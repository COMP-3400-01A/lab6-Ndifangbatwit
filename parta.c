#include "parta.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Creates an array of PCBs from the burst array.
 * Each PCB is initialized with a PID, burst_left, and wait time of 0.
 */

struct pcb* init_procs(int* bursts, int blen) {
     struct pcb* procs = malloc(sizeof(struct pcb) * blen);

    for (int i = 0; i < blen; i++) {
        procs[i].pid = i;
        procs[i].burst_left = bursts[i];
        procs[i].wait = 0;
    }

    return procs;
}

/**
 * Prints all PCB values.
 */
void printall(struct pcb* procs, int plen) {
    for (int i = 0; i < plen; i++) {
        printf("P%d Burst:%d Wait:%d\n",
               procs[i].pid,
               procs[i].burst_left,
               procs[i].wait);
    }
}

/**
 * Runs one process for the specified amount of time.
 * Decreases its remaining burst and increases every
 * other unfinished process's wait time.
 */
void run_proc(struct pcb* procs, int plen, int current, int amount) {
    if (amount > procs[current].burst_left)
        amount = procs[current].burst_left;

    procs[current].burst_left -= amount;

    for (int i = 0; i < plen; i++) {
        if (i != current && procs[i].burst_left > 0) {
            procs[i].wait += amount;
        }
    }
}

/**
 * Executes First-Come First-Serve scheduling.
 * Returns total elapsed time.
 */
int fcfs_run(struct pcb* procs, int plen) {
     int time = 0;

    for (int i = 0; i < plen; i++) {
        int burst = procs[i].burst_left;
        run_proc(procs, plen, i, burst);
        time += burst;
    }

    return time;
}

/**
 * Returns the next runnable process for Round Robin.
 * Returns -1 if every process has completed.
 */
int rr_next(int current, struct pcb* procs, int plen) {
     for (int i = 1; i <= plen; i++) {
        int next = (current + i) % plen;

        if (procs[next].burst_left > 0)
            return next;
    }
    return -1;
}
/**
 * Executes Round Robin scheduling.
 * Returns total elapsed time.
 */
int rr_run(struct pcb* procs, int plen, int quantum) {
     int time = 0;
    int current = 0;

    while (current != -1) {

        int slice = quantum;

        if (procs[current].burst_left < quantum)
            slice = procs[current].burst_left;

        run_proc(procs, plen, current, slice);
        time += slice;

        current = rr_next(current, procs, plen);
    }

    return time;
}

