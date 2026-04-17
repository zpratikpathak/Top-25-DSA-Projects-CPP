#include <iostream>
#include <vector>

#define N 9

class SudokuSolver {
    int grid[N][N];

public:
    SudokuSolver(int inputGrid[N][N]) {
        for(int i=0; i<N; i++) for(int j=0; j<N; j++) grid[i][j] = inputGrid[i][j];
    }

    bool isSafe(int row, int col, int num) {
        for (int x = 0; x < 9; x++) if (grid[row][x] == num) return false;
        for (int x = 0; x < 9; x++) if (grid[x][col] == num) return false;
        int startRow = row - row % 3, startCol = col - col % 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[i + startRow][j + startCol] == num) return false;
        return true;
    }

    bool solve() {
        int row, col;
        bool empty = false;
        for (row = 0; row < N; row++) {
            for (col = 0; col < N; col++) {
                if (grid[row][col] == 0) { empty = true; break; }
            }
            if (empty) break;
        }
        if (!empty) return true;

        for (int num = 1; num <= 9; num++) {
            if (isSafe(row, col, num)) {
                grid[row][col] = num;
                if (solve()) return true;
                grid[row][col] = 0;
            }
        }
        return false;
    }

    void print() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) std::cout << grid[i][j] << " ";
            std::cout << "\n";
        }
    }
};

int main() {
    int board[N][N] = { {3, 0, 6, 5, 0, 8, 4, 0, 0},
                        {5, 2, 0, 0, 0, 0, 0, 0, 0},
                        {0, 8, 7, 0, 0, 0, 0, 3, 1},
                        {0, 0, 3, 0, 1, 0, 0, 8, 0},
                        {9, 0, 0, 8, 6, 3, 0, 0, 5},
                        {0, 5, 0, 0, 9, 0, 6, 0, 0},
                        {1, 3, 0, 0, 0, 0, 2, 5, 0},
                        {0, 0, 0, 0, 0, 0, 0, 7, 4},
                        {0, 0, 5, 2, 0, 6, 3, 0, 0} };
    SudokuSolver ss(board);
    if (ss.solve()) ss.print();
    else std::cout << "No solution exists";
    return 0;
}
