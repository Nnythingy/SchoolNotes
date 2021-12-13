#include "packer.h"
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// You can declare global variables here
// Index 0 = colour
// Index 1 = id
// Index 2 = deleted flag
int maxBalls;
sem_t writing;
//sem_t reading;

int packingArea[4][1000][2] = {0};
int counter[4]= {0};
sem_t semColour[4];
sem_t pack[4];
sem_t mutex[4];

void packer_init(int balls_per_pack) {
    // Write initialization code here (called once at the start of the program).
    // It is guaranteed that balls_per_pack >= 2.
    maxBalls = balls_per_pack;
    sem_init(&writing, 0, 1);
    //sem_init(&reading);
    for (int i = 0; i < 4; i++) {
        sem_init(&semColour[i], 0, 1);
        sem_init(&pack[i], 0, 0);
        sem_init(&mutex[i], 0, 1);
        //packingArea[i] = (int *)malloc(balls_per_pack * sizeof(int));
    }
}

void packer_destroy(void) {
    // Write deinitialization code here (called once at the end of the program).
    sem_destroy(&writing);
    //sem_destroy(&reading);
    for (int i = 0; i < 4; i++) {
        sem_destroy(&semColour[i]);
        sem_destroy(&pack[i]);
        sem_destroy(&mutex[i]);
        //free(packingArea[i]);
    }
}

void add_ball(int colour, int id) {
    for (int i = 0; i < maxBalls; i++) {
        if (packingArea[colour][i][0] == 0) {
            packingArea[colour][i][0] = id;
            return;
        }
    }
}

void pack_ball(int colour, int id, int *other_ids) {
    // Write your code here.
    // Remember to populate the array `other_ids` with the (balls_per_pack-1) other balls.

    sem_wait(&semColour[colour]);
    sem_wait(&mutex[colour]);
    sem_wait(&writing);
    counter[colour] += 1;
    sem_post(&writing);

    if (counter[colour] == maxBalls) {
        sem_wait(&writing);
        counter[colour] = 0;
        add_ball(colour, id);
        int index = 0;
        for (int a = 0; a < maxBalls; a++) {
            if (index == maxBalls) break;
            if (packingArea[colour][a][0] == id && packingArea[colour][a][1] == 1) {
                packingArea[colour][a][1] = 1;
                continue;
            }
            other_ids[index] = packingArea[colour][a][0];
            packingArea[colour][a][1] = 1;
            index += 1;
        }
        sem_post(&writing);

        sem_post(&mutex[colour]);
        for (int i = 0; i < maxBalls-1; i++) {
            sem_post(&pack[colour]);
        }
        return;
    }

    sem_post(&semColour[colour]);
    sem_wait(&writing);
    add_ball(colour, id);
    sem_post(&writing);
    sem_post(&mutex[colour]);

    sem_wait(&pack[colour]);
    sem_wait(&writing);
    int index = 0;
    for (int a = 0; a < 1000; a++) {
        if (index == maxBalls) break;
        if (packingArea[colour][a][0] == id && packingArea[colour][a][1] == 1) {
            packingArea[colour][a][1] = 1;
            continue;
        }
        other_ids[index] = packingArea[colour][a][0];
        packingArea[colour][a][1] = 1;
        index += 1;
    }
    sem_post(&writing);

    sem_post(&semColour[colour]);
    return;
}
