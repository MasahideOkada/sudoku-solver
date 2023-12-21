#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdint.h>

typedef uint8_t CellVal;
typedef CellVal Grid[81];
typedef uint8_t CandidateArray[729];

typedef struct {
    Grid grid;
    CandidateArray candidate_array;
} GridState;

typedef enum {
    SOLVED,
    UNSOLVED,
    INVALID_GRID,
} SudokuState;

void show_grid(Grid* grid);
void make_candidate_array(CandidateArray* candidate_array, Grid* grid);
void show_candidates(CandidateArray* candidate_array);
void init_grid_state(GridState* state, Grid* grid);
SudokuState check_sudoku_state(Grid *grid);

#endif
