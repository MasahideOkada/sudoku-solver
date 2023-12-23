#include "grid.h"

void show_grid(Grid* grid) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int cell_id = 9 * row + col;
            printf("%d ", (*grid)[cell_id]);
        }
        printf("\n");
    } 
}

void make_candidate_array(CandidateArray* candidate_array, Grid* grid) {
    for (int cell_id = 0; cell_id < 81; ++cell_id) {
        int row = cell_id / 9;
        int col = cell_id % 9;
        CellVal cell_val = (*grid)[cell_id];

        if (cell_val != 0) {
            int cand_id = 9 * cell_id + (cell_val - 1);
            (*candidate_array)[cand_id] = 1;
        } else {
            // the indices for this array corresponds to the cell value
            // if the index (cell value) exists in other cells in same region, 
            // the element of this array becomes 1
            int value_check_array[10] = {0};
            int box_top_row = 3 * (row / 3);
            int box_left_col = 3 * (col / 3);
            for (int k = 0; k < 9; ++k) {
                int same_row_cell_id = 9 * row + k;
                CellVal same_row_cell_val = (*grid)[same_row_cell_id];

                int same_col_cell_id = 9 * k + col;
                CellVal same_col_cell_val = (*grid)[same_col_cell_id];

                int inbox_row = k / 3;
                int inbox_col = k % 3;
                int same_box_cell_id = 9 * (box_top_row + inbox_row) + (box_left_col + inbox_col);
                CellVal same_box_cell_val = (*grid)[same_box_cell_id];

                value_check_array[same_row_cell_val] = 1;
                value_check_array[same_col_cell_val] = 1;
                value_check_array[same_box_cell_val] = 1;
            }

            for (int n = 0; n < 9; ++n) {
                int cand_val = n + 1;
                int cand_id = 9 * cell_id + n;
                (*candidate_array)[cand_id] = (uint8_t)(value_check_array[cand_val] == 0);
            }
        }
    }    
}

void init_grid_state(GridState* state, Grid* grid) {
    for (int cell_id = 0; cell_id < 81; ++cell_id) {
        CellVal cell_val = (*grid)[cell_id];
        state->grid[cell_id] = cell_val;
    }
    for (int i = 0; i < 729; ++i) state->candidate_array[i] = 0;
    make_candidate_array(&state->candidate_array, grid);
}

void show_candidates(CandidateArray* candidata_array) {
    printf("candidates\n");

    for (int cell_id = 0; cell_id < 81; ++cell_id) {
        int row = cell_id / 9;
        int col = cell_id % 9;
        printf("(%d, %d): ", row + 1, col + 1);

        for (int n = 0; n < 9; ++n) {
            CellVal val = (CellVal)(n + 1);
            int cand_id = 9 * cell_id + n;
            if ((*candidata_array)[cand_id]) printf("%d ", val);
        }
        printf("\n");
    }
}

SudokuState check_sudoku_state(Grid *grid) {
    uint8_t num_filled_blocks = 0;
    SudokuState sudoku_state = UNSOLVED;
    
    // check value uniqueness in each row
    for (int row = 0; row < 9; ++row) {
        uint8_t num_unique_vals = 0;
        for (int val = 1; val < 10; ++val) {
            uint8_t count = 0;
            uint8_t col_array[9] = {0};

            for (int col = 0; col < 9; ++col) {
                int cell_id = 9 * row + col;
                CellVal cell_val = (*grid)[cell_id];
                if (cell_val == val) {
                    col_array[count++] = col;
                }
            }

            if (count == 1) ++num_unique_vals;
            if (count > 1) {
                printf("invalid sudoku: %d appears %d times in row %d at ", val, count, row + 1);
                for (int i = 0; i < count; ++i){
                    printf("(%d, %d) ", row + 1, col_array[i] + 1);
                }
                printf("\n");

                sudoku_state = INVALID_GRID;
            }
        }

        if (num_unique_vals == 9) ++num_filled_blocks;
    }

    // check value uniqueness in each column
    for (int col = 0; col < 9; ++col) {
        uint8_t num_unique_vals = 0;
        for (int val = 1; val < 10; ++val) {
            int count = 0;
            uint8_t row_array[9] = {0};

            for (int row = 0; row < 9; ++row) {
                int cell_id = 9 * row + col;
                CellVal cell_val = (*grid)[cell_id];
                if (cell_val == val) {
                    row_array[count++] = row;
                }
            }

            if (count == 1) ++num_unique_vals;
            if (count > 1) {
                printf("invalid sudoku: %d appears %d times in column %d at ", val, count, col+1);
                for (int i = 0; i < count; ++i){
                    printf("(%d, %d) ", row_array[i] + 1 , col + 1);
                }
                printf("\n");

                sudoku_state = INVALID_GRID;
            }
        }

        if (num_unique_vals == 9) ++num_filled_blocks;
    }

    // check value uniqueness in each 3x3 box
    for (int box = 0; box < 9; ++box) {
        int box_top_row = 3 * (box / 3);
        int box_left_col = 3 * (box % 3);

        uint8_t num_unique_vals = 0;
        for (int val = 1; val < 10; ++val) {
            uint8_t count = 0;
            uint8_t inbox_array[9] = {0};

            for (int inbox = 0; inbox < 9; ++inbox) {
                int inbox_row = inbox / 3;
                int inbox_col = inbox % 3;

                int cell_id = 9 * (box_top_row + inbox_row) + (box_left_col + inbox_col);
                CellVal cell_val = (*grid)[cell_id];
                if (cell_val == val) {
                    inbox_array[count++] = inbox;
                }
            }

            if (count == 1) ++num_unique_vals;
            if (count > 1) {
                printf("invalid sudoku: %d appears %d times in box %d at ", val, count, box+1);
                for (int i = 0; i < count; ++i){
                    int inbox_id = inbox_array[i];
                    int inbox_row = inbox_id / 3;
                    int inbox_col = inbox_id % 3;
                    int row = box_top_row + inbox_row;
                    int col = box_left_col + inbox_col;
                    printf("(%d, %d) ", row + 1, col + 1);
                }
                printf("\n");

                sudoku_state = INVALID_GRID;
            }
        }

        if (num_unique_vals == 9) ++num_filled_blocks;
    }

    if (num_filled_blocks == 27) sudoku_state = SOLVED;
    return sudoku_state;
}
