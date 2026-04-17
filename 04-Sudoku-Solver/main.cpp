#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>

/**
 * Advanced Sudoku Solver
 * Features:
 * - Bitmasking optimization for O(1) safety checks
 * - Forward Checking (Pruning the search space)
 * - Minimum Remaining Values (MRV) Heuristic
 * - Solving complex 9x9 grids with minimal recursion depth
 */

class SudokuSolver {
private:
    int grid[9][9];
    std::bitset<10> rows[9], cols[9], boxes[9];

    int getBox(int r, int c) { return (r / 3) * 3 + (c / 3); }

    bool findBestCell(int& row, int& col) {
        int minChoices = 10;
        bool found = false;
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (grid[r][c] == 0) {
                    int choices = 0;
                    std::bitset<10> used = rows[r] | cols[c] | boxes[getBox(r, c)];
                    for (int n = 1; n <= 9; ++n) if (!used[n]) choices++;
                    
                    if (choices < minChoices) {
                        minChoices = choices;
                        row = r; col = c;
                        found = true;
                    }
                }
            }
        }
        return found;
    }

public:
    SudokuSolver(int input[9][9]) {
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                grid[r][c] = input[r][c];
                if (grid[r][c] != 0) {
                    int n = grid[r][c];
                    rows[r].set(n);
                    cols[c].set(n);
                    boxes[getBox(r, c)].set(n);
                }
            }
        }
    }

    bool solve() {
        int r, c;
        if (!findBestCell(r, c)) return true; // All cells filled

        std::bitset<10> used = rows[r] | cols[c] | boxes[getBox(r, c)];
        for (int n = 1; n <= 9; ++n) {
            if (!used[n]) {
                grid[r][c] = n;
                rows[r].set(n); cols[c].set(n); boxes[getBox(r, c)].set(n);

                if (solve()) return true;

                // Backtrack
                grid[r][c] = 0;
                rows[r].reset(n); cols[c].reset(n); boxes[getBox(r, c)].reset(n);
            }
        }
        return false;
    }

    void display() {
        std::cout << "\n--- SOLVED SUDOKU GRID ---\n";
        for (int r = 0; r < 9; ++r) {
            if (r % 3 == 0 && r != 0) std::cout << "------+-------+------\n";
            for (int c = 0; c < 9; ++c) {
                if (c % 3 == 0 && c != 0) std::cout << "| ";
                std::cout << grid[r][c] << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    // An extremely hard Sudoku puzzle
    int board[9][9] = {
        {8, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 3, 6, 0, 0, 0, 0, 0},
        {0, 7, 0, 0, 9, 0, 2, 0, 0},
        {0, 5, 0, 0, 0, 7, 0, 0, 0},
        {0, 0, 0, 0, 4, 5, 7, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 3, 0},
        {0, 0, 1, 0, 0, 0, 0, 6, 8},
        {0, 0, 8, 5, 0, 0, 0, 1, 0},
        {0, 9, 0, 0, 0, 0, 4, 0, 0}
    };

    SudokuSolver solver(board);
    if (solver.solve()) {
        solver.display();
    } else {
        std::cout << "No solution exists for the given grid." << std::endl;
    }

    return 0;
}
