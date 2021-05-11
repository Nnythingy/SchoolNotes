#include "cs1010.h"
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>

#define LIVE '#'
#define DEAD '.'

bool is_alive(char cell) {
  return cell == LIVE;
}

bool is_dead(char cell) {
  return cell == DEAD;
}

void kill(char *cell) {
  *cell = DEAD;
}

void born(char *cell) {
  *cell = LIVE;
}

void swap(char ***a, char ***b) {
  char **temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

void print_universe(long nrows, char **universe) {
  for (long i = 0; i < nrows; i += 1) {
    cs1010_print_string(universe[i]);
  }
}

/**
 * Count the number of neighbors that is alive.
 *
 * @param[in] universe The game of life universe
 * @param[in] i The row coordinate of the current cell whose 
 *              neighbors we are counting.
 * @param[in] j The column coordinate of the current cell whose 
 *              neighbors we are counting.
 * @return The number of live neighbors.
 */
long count_live_neighbor(char **universe, long i, long j) {
  long count = 0;
  for (long x = -1; x <= 1; x += 1) {
    for (long y = -1; y <= 1; y += 1) {
      if (x != 0 || y != 0) {
        if (universe[i+x] == NULL) {
          return 0;
        }
        if (is_alive(universe[i+x][j+y])) {
          count += 1;
        }
      }
    }
  }
  return count;
}

/**
 * Update the cell (i, j) in the universe.
 *
 * @param[in] universe The game of life universe
 * @param[in] i The row coordinate of the current cell we are updating
 * @param[in] j The column coordinate of the current cell we are updating
 * @return The new status of the cell (DEAD or LIVE)
 */
char update_cell(char **universe, long i, long j) {
  long live_neighbor_count = count_live_neighbor(universe, i, j);
  if (universe[i] == NULL) {
    return 0;
  }
  if (is_alive(universe[i][j])) {
    if (live_neighbor_count < 2 || live_neighbor_count > 3) {
      return DEAD;
    } 
  } else { 
    if (live_neighbor_count == 3) {
      return LIVE;
    }
  } 
  return universe[i][j];
}

/**
 * Simulate one step of the game of life.
 *
 * @param[in] nrows The number of rows
 * @param[in] ncols The number of columns
 * @param[in] universe The curr game of life universe
 * @param[out] next_universe The updated game of life universe
 */
void simulate_game(long nrows, long ncols, char **universe, char **next_universe) {
  for (long i = 1; i < nrows-1; i += 1) {
    for (long j = 1; j < ncols-1; j += 1) {
      if (next_universe[i] == NULL) {
          return;
      }
      next_universe[i][j] = update_cell(universe, i, j);
    }
  }
}

int main()
{
  long nrows = cs1010_read_long();
  long ncols = cs1010_read_long();
  long k = cs1010_read_long();
  char **universe = calloc((size_t)nrows, sizeof(char *));
  if (universe == NULL) {
      return 1;
  }

  for (long i = 0; i < nrows; i += 1) {
    universe[i] = cs1010_read_line();
    if (universe[i] == NULL) {
        free(universe);
        return 1;
    }
  }

  char **next_universe = calloc((size_t)nrows, sizeof(char *));
  if (next_universe == NULL) {
      free(universe);
      return 1;
  }
  for (long i = 0; i < nrows; i += 1) {
    next_universe[i] = calloc((size_t)ncols + 2, sizeof(char));
    if (next_universe[i] == NULL) {
        free(universe);
        free(next_universe);
        return 1;
    }
  }
  for (long i = 0; i < nrows; i += 1) {
    for (long j = 0; j < ncols; j += 1) {
      next_universe[i][j] = '.';
    }
    next_universe[i][ncols] = '\n';
  }

  for (long i = 0; i < k; i += 1) {
    simulate_game(nrows, ncols, universe, next_universe);
    cs1010_clear_screen();
    print_universe(nrows, next_universe);
    usleep(25*10); 
    swap(&universe, &next_universe);
  }

  for (long i = 0; i < nrows; i += 1) {
    free(universe[i]);
    free(next_universe[i]);
  }
  free(universe);
  free(next_universe);
}