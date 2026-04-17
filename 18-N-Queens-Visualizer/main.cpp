#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

/**
 * Advanced N-Queens Visualizer
 * Features:
 * - Backtracking algorithm to find ALL possible solutions
 * - Optimized safety checks
 * - Formatted console visualization
 * - Performance tracking (Count of configurations explored)
 */

class NQueensEngine {
private:
    int N;
    int solutionsCount = 0;
    int nodesExplored = 0;
    std::vector<std::vector<int>> board;

    bool isSafe(int row, int col) {
        nodesExplored++;
        // Check this row on left side
        for (int i = 0; i < col; i++) if (board[row][i]) return false;

        // Check upper diagonal on left side
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) if (board[i][j]) return false;

        // Check lower diagonal on left side
        for (int i = row, j = col; j >= 0 && i < N; i++, j--) if (board[i][j]) return false;

        return true;
    }

    void solveRecursive(int col) {
        if (col >= N) {
            solutionsCount++;
            if (solutionsCount <= 3) displayBoard(); // Show first 3 solutions
            return;
        }

        for (int i = 0; i < N; i++) {
            if (isSafe(i, col)) {
                board[i][col] = 1;
                solveRecursive(col + 1);
                board[i][col] = 0; // Backtrack
            }
        }
    }

    void displayBoard() {
        std::cout << "\nSolution #" << solutionsCount << std::endl;
        std::cout << "  ";
        for(int i=0; i<N; i++) std::cout << "---";
        std::cout << "\n";
        for (int i = 0; i < N; i++) {
            std::cout << "| ";
            for (int j = 0; j < N; j++) {
                std::cout << (board[i][j] ? " Q " : " . ");
            }
            std::cout << "|\n";
        }
        std::cout << "  ";
        for(int i=0; i<N; i++) std::cout << "---";
        std::cout << "\n";
    }

public:
    NQueensEngine(int n) : N(n), board(n, std::vector<int>(n, 0)) {}

    void findSolutions() {
        std::cout << "[SYSTEM] Computing all solutions for " << N << "-Queens..." << std::endl;
        solveRecursive(0);
        std::cout << "\n--- FINISHED ---" << std::endl;
        std::cout << "Total Solutions: " << solutionsCount << std::endl;
        std::cout << "Nodes Explored:  " << nodesExplored << std::endl;
        std::cout << "----------------\n" << std::endl;
    }
};

int main() {
    NQueensEngine engine(8);
    engine.findSolutions();
    return 0;
}
