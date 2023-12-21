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

        // if the count is one and the cell is blanc, it's a naked single
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
