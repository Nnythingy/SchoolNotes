#include "restaurant.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

// You can declare global variables here
sem_t table_sem[5];
int **tables[5];

void restaurant_init(int num_tables[5]) {
    // Write initialization code here (called once at the start of the program).
    // It is guaranteed that num_tables is an array of length 5.
    int tableid = 0;
    for (int i = 0; i < 5; i++) {
        sem_init(&table_sem[i], 0, num_tables[i]);
        tables[i] = (int **)malloc((1+num_tables[i])*sizeof(int *));
        for (int j = 1; j <= num_tables[i]; j++) {
            // index 0 = table id
            // index 1 = group id
            tables[i][j] = (int *)malloc(2*sizeof(int));
            tables[i][j][0] = tableid;
            tableid++;

        }
            // storing the table capacity
            tables[i][0][0] = num_tables[i];
            printf("%d\n",tables[i][0][0]);
    }
    for (int i = 0; i < 5; i++) {
        printf("test %d", tables[i][0][0]);
        printf("table %d: ", i+1);
        for (int j = 1; j <= tables[i][0][0]; j++) {
            printf("%d, ", tables[i][j][0]);
        }
        printf("\n");
    }
}

void restaurant_destroy(void) {
    // Write deinitialization code here (called once at the end of the program).
    for (int i = 0; i < 5; i++) {
        for (int j = 1; j <= tables[i][0][0]; j++) {
            free(tables[i][j]);
        }
        free(tables[i]);
        sem_destroy(&table_sem[i]);
    }
}

int request_for_table(group_state *state, int num_people) {
    // Write your code here.
    // Return the id of the table you want this group to sit at.
    
    /*
    sem_wait(&table_sem[num_people-1]);
    for (int i = 1; i <= tables[num_people-1][0][0]; i++) {
        if (tables[num_people-1][i][1] == 0) {
            tables[num_people-1][i][1] = state->gid;
            printf("%d\n", tables[num_people-1][i][1]);
            state->tid = tables[num_people-1][i][0];
            state->num = num_people;
            return tables[num_people-1][i][0];
        }
    }
    */
    return 0;
}

void leave_table(group_state *state) {
    // Write your code here.
    // TODO
}
