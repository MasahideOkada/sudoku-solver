#include <stdio.h>

#include "grid.h"
#include "basic_techniques.h"

// Naked singles are the candidates that is the only one in a cell
void find_naked_singles(GridState* state) {
    for (int cell_id = 0; cell_id < 81; ++cell_id) {
        uint8_t count = 0;
        CellVal cand_val = 0;
        // count the number of candidate
        for (int n = 0; n < 9; ++n) {
            int cand_id = 9 * cell_id + n;
            uint8_t is_cand = state->candidate_array[cand_id];
            count += is_cand;
            cand_val = is_cand ? (CellVal)(n + 1) : cand_val;
        }

        // if the count is one and the cell is not filled, it's a naked single
        CellVal cell_val = state->grid[cell_id];
        if (count == 1 && cell_val == 0) {
            // the cell is filled
            state->grid[cell_id] = cand_val;

            int row = cell_id / 9;
            int col = cell_id % 9;
            printf("Naked single %d at (%d, %d)\n", cand_val, row + 1, col + 1);
        }
    }
}

// Hidden singles are the candidates that appears only once in a block(row, column, or 3x3 box)
void find_hidden_singles(GridState* state) {
    // check rows
    for (int row = 0; row < 9; ++row){
        // to count how many times a candidate appear
        uint8_t cand_count_array[9] = {0};
        // to store the last column containing a value
        int col_array[9] = {0};
        for (int n = 0; n < 9; ++n) {
            for (int col = 0; col < 9; ++col) {
                int cell_id = 9 * row + col;
                int cand_id = 9 * cell_id + n;
                uint8_t is_cand = state->candidate_array[cand_id];
                cand_count_array[n] += is_cand;
                if (is_cand) col_array[n] = col;
            }
        }

        // check hidden singles
        for (int n = 0; n < 9; ++n) {
            if (cand_count_array[n] == 1) {
                int col = col_array[n];
                int cell_id = 9 * row + col;
                CellVal cell_val = state->grid[cell_id];
                // if the cell is not filled, it has a hidden single
                if (cell_val == 0) {
                    printf("Hidden single %d at (%d, %d) for row %d\n", n + 1, row + 1, col + 1, row + 1);
                }
            }
        }
    }
    // check cols
    for (int col = 0; col < 9; ++col){
        // to count how many times a candidate appear
        uint8_t cand_count_array[9] = {0};
        // to store the last column containing a value
        int row_array[9] = {0};
        for (int n = 0; n < 9; ++n) {
            for (int row = 0; row < 9; ++row) {
                int cell_id = 9 * row + col;
                int cand_id = 9 * cell_id + n;
                uint8_t is_cand = state->candidate_array[cand_id];
                cand_count_array[n] += is_cand;
                if (is_cand) row_array[n] = row;
            }
        }

        // check hidden singles
        for (int n = 0; n < 9; ++n) {
            if (cand_count_array[n] == 1) {
                int row = row_array[n];
                int cell_id = 9 * row + col;
                CellVal cell_val = state->grid[cell_id];
                // if the cell is not filled, it has a hidden single
                if (cell_val == 0) {
                    printf("Hidden single %d at (%d, %d) for column %d\n", n + 1, row + 1, col + 1, row + 1);
                }
            }
        }
    }
    // check 3x3 boxes
    for (int box = 0; box < 9; ++box){
        int box_top_row = 3 * (box / 3);
        int box_left_col = 3 * (box % 3);
        // to count how many times a candidate appear
        uint8_t cand_count_array[9] = {0};
        // to store the last column containing a value
        int inbox_array[9] = {0};
        for (int n = 0; n < 9; ++n) {
            for (int inbox = 0; inbox < 9; ++inbox) {
                int inbox_row = inbox / 3;
                int inbox_col = inbox % 3;

                int cell_id = 9 * (box_top_row + inbox_row) + (box_left_col + inbox_col);
                int cand_id = 9 * cell_id + n;
                uint8_t is_cand = state->candidate_array[cand_id];
                cand_count_array[n] += is_cand;
                if (is_cand) inbox_array[n] = inbox;
            }
        }

        // check hidden singles
        for (int n = 0; n < 9; ++n) {
            if (cand_count_array[n] == 1) {
                int inbox = inbox_array[n];
                int inbox_row = inbox / 3;
                int inbox_col = inbox % 3;
                int row = box_top_row + inbox_row;
                int col = box_left_col + inbox_col;

                int cell_id = 9 * row + col;
                CellVal cell_val = state->grid[cell_id];
                // if the cell is not filled, it has a hidden single
                if (cell_val == 0) {
                    printf("Hidden single %d at (%d, %d) for box %d\n", n + 1, row + 1, col + 1, box + 1);
                }
            }
        }
    }    
}
