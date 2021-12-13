#include "packer.h"
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

// You can declare global variables here
// Index 0 = colour
// Index 1 = id
// Index 2 = deleted flag
int packingArea[4][2]= {0};
int counter[4]= {0};
sem_t semColour[4];
sem_t pack[4];
sem_t mutex[4];

void packer_init(void) {
    // Write initialization code here (called once at the start of the program).
    for (int i = 0; i < 4; i++) {
        sem_init(&semColour[i], 0, 1);
        sem_init(&pack[i], 0, 0);
        sem_init(&mutex[i], 0, 1);
    }
}

void packer_destroy(void) {
    // Write deinitialization code here (called once at the end of the program).
    for (int i = 0; i < 4; i++) {
        sem_destroy(&semColour[i]);
        sem_destroy(&pack[i]);
        sem_destroy(&mutex[i]);
    }
}

int pack_ball(int colour, int id) {
    // Write your code here.
    sem_wait(&semColour[colour]);
    sem_wait(&mutex[colour]);
    counter[colour] += 1;

    // release sem
    if (counter[colour] == 2) {
        packingArea[colour][1] = id;
        counter[colour] = 0;

        int ans = packingArea[colour][0];
        sem_post(&mutex[colour]);
        sem_post(&pack[colour]);
        return ans;
    }

    sem_post(&semColour[colour]);
    packingArea[colour][0] = id;
    sem_post(&mutex[colour]);
    sem_wait(&pack[colour]);
    int ans = packingArea[colour][1];
    sem_post(&semColour[colour]);
    return ans;
}
