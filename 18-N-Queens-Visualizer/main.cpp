#include <iostream>
#include <vector>

#define N 8

class NQueens {
    int board[N][N];

public:
    NQueens() {
        for(int i=0; i<N; i++) for(int j=0; j<N; j++) board[i][j] = 0;
    }

    bool isSafe(int row, int col) {
        int i, j;
        for (i = 0; i < col; i++) if (board[row][i]) return false;
        for (i = row, j = col; i >= 0 && j >= 0; i--, j--) if (board[i][j]) return false;
        for (i = row, j = col; j >= 0 && i < N; i++, j--) if (board[i][j]) return false;
        return true;
    }

    bool solve(int col) {
        if (col >= N) return true;
        for (int i = 0; i < N; i++) {
            if (isSafe(i, col)) {
                board[i][col] = 1;
                if (solve(col + 1)) return true;
                board[i][col] = 0;
            }
        }
        return false;
    }

    void print() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) std::cout << (board[i][j] ? "Q " : ". ");
            std::cout << "\n";
        }
    }
};

int main() {
    NQueens nq;
    if (nq.solve(0)) nq.print();
    else std::cout << "No solution exists";
    return 0;
}
