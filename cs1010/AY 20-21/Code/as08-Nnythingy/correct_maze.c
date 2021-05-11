#include "cs1010.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define EMPTY '.'
#define WALL  '#'
#define USER  '@'

/**
 * Print the maze to the screen.
 * 
 * @param[in] maze The 2D array representing the maze.
 * @param[in] nrows The number of rows
 * @param[in] steps The number of steps taken so far.
 */
void print_maze(char **maze, long nrows, long steps) {
    cs1010_clear_screen();
    for (long i = 0; i < nrows; i += 1) {
        cs1010_println_string(maze[i]);
    }
    cs1010_println_long(steps);
    if (isatty(fileno(stdout))) {
        usleep(100*1000);
    }
}

/**
 * Try to move one step in the maze in the given direction.
 * 
 * @param[in,out] maze The 2D array representing the maze.
 * @param[in]     x    The current x position.
 * @param[in]     y    The current y position.
 * @param[in]     dx   The x direction to move (-1, 0, 1).
 * @param[in]     dy   The y direction to move (-1, 0, 1).
 * @param[in,out] steps The number of steps taken so far.
 *
 * @return true if we successfully moved.  false otherwise.
 */
bool move_one_step(char **maze, long x, long y, long dx, long dy, long *steps) 
{
    if (maze[x + dx][y + dy] != EMPTY) {
        return false;
    }

    maze[x][y] = EMPTY;
    maze[x + dx][y + dy] = USER;
    *steps += 1;

    return true;
}

bool visit(char **maze, bool **visited, long width, long length, long x, long y, long dx, long dy, long *steps);

/**
 * Try to escape the maze from the position x, y.
 * 
 * @param[in]     maze    The 2D array representing the maze.
 * @param[in,out] visited The 2D array to remember whether a cell has been
 *                        visited before.
 * @param[in]     m       The number of rows in the maze.
 * @param[in]     n       The number of cols in the maze.
 * @param[in]     x       The x position of Scully.
 * @param[in]     y       The y position of Scully.
 * @param[in,out] steps   The num of steps that has been taken.
 */
bool escape(char **maze, bool **visited, long m, long n, long x, long y, long *steps){

    if (visited != NULL && visited[x] != NULL) {
        visited[x][y] = true;
    }

    // If already at the border, then escape.
    if (x == 0 || x == m-1 || y == 0 || y == n-1) {
        return true;
    }

    for (long dir = 0; dir < 4; dir += 1) {
        // For each direction.
        char delta[4][2]={
            {-1, 0},
            {0,  1},
            {1,  0},
            {0, -1}
        };
        char dx = delta[dir][0];
        char dy = delta[dir][1];

        if (!visited[x + dx][y + dy]) {
            if (visit(maze, visited, m, n, x, y, dx, dy, steps)) {
                return true;
            }
        }
    }
    return false;
}

bool visit(char **maze, bool **visited, long width, long length, long x, long y, long dx, long dy, long *steps)
{
    bool can_move = move_one_step(maze, x, y, dx, dy, steps);
    if (can_move) {
        print_maze(maze, width, *steps);
        if (escape(maze, visited, width, length, x+dx, y+dy, steps)) {
            return true;
        }
        move_one_step(maze, x+dx, y+dy, -dx, -dy, steps);
        print_maze(maze, width, *steps);
    }
    return false;
}

char **read_2d_array(size_t m) {
    char **mem = calloc(m, sizeof(char *));
    if (mem == NULL) {
        cs1010_println_string("unable to allocate maze");
        return NULL;
    }
    for (size_t i = 0; i < m; i += 1) {
        mem[i] = cs1010_read_word();
        if (mem[i] == NULL) {
            for (size_t j = 0; j < i; j += 1) {
                free(mem[j]);
            }
            free(mem);
            cs1010_println_string("unable to allocate maze");
            return NULL;
        }
    }
    return mem;
}

bool **allocate_2d_array(size_t m, size_t n) {
    bool **mem = calloc(m, sizeof(bool *));
    if (mem == NULL) {
        cs1010_println_string("unable to allocate maze");
        return NULL;
    }
    for (size_t i = 0; i < m; i += 1) {
        mem[i] = calloc(n, sizeof(bool));
        if (mem[i] == NULL) {
            for (size_t j = 0; j < i; j += 1) {
                free(mem[j]);
            }
            free(mem);
            cs1010_println_string("unable to allocate maze");
            return NULL;
        }
    }
    return mem;
}

void free_2d_array(void **a, size_t m) {
    for (size_t i = 0; i < m; i += 1) {
        free(a[i]);
    }
    free(a);
}

int main() {
    char **maze;
    bool **visited;
    long m;
    long n;
    m = cs1010_read_long();
    n = cs1010_read_long();
    maze = read_2d_array((size_t)m);
    if (maze == NULL) {
        return 1;
    }
    visited = allocate_2d_array((size_t)m, (size_t)n);
    if (visited == NULL) {
        free_2d_array((void **)maze, (size_t)m);
        return 1;
    }

    long startx = 0;
    long starty = 0;
    for (long i = 0; i < m; i += 1) {
        for (long j = 0;j < n; j += 1) {
            if (maze[i][j]=='@') {
                startx = i;
                starty = j;
            }
        }
    }

    long steps = 0;
    print_maze(maze, m, steps);
    escape(maze, visited, m, n, startx, starty, &steps);	

    free_2d_array((void **)maze, (size_t)m);
    free_2d_array((void **)visited, (size_t)m);
}