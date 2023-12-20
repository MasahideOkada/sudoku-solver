#include <stdio.h>

#include "grid.h"

int main() {        
    Grid grid = {
        0, 9, 0, 0, 0, 0, 3, 0, 0,
        5, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 3, 4, 0, 0, 0, 0, 0, 7,
        0, 1, 9, 2, 8, 7, 0, 0, 0,
        4, 0, 0, 0, 0, 0, 0, 0, 6,
        0, 2, 0, 9, 0, 0, 0, 0, 0,
        0, 0, 2, 0, 0, 6, 0, 0, 9,
        0, 0, 0, 0, 0, 1, 7, 0, 0,
        0, 4, 0, 0, 0, 9, 8, 0, 0,
    };
    //show_grid(&grid);
    //CandidateArray candidate_array = {0};
    //make_candidate_array(&candidate_array, &grid);
    //show_candidates(&candidate_array);
    SudokuState sudoku_state = check_sudoku_state(&grid);
    switch (sudoku_state) {
        case SOLVED:
            printf("solved\n");
            break;
        case UNSOLVED:
            printf("unsolved\n");
            break;
        default:
            break;
    }
    return 0;
}
