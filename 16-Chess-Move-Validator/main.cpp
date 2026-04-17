#include <iostream>
#include <string>
#include <cmath>

class ChessValidator {
public:
    static bool isValidMove(std::string piece, int x1, int y1, int x2, int y2) {
        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);

        if (piece == "Rook") return (x1 == x2 || y1 == y2);
        if (piece == "Bishop") return (dx == dy);
        if (piece == "Queen") return (x1 == x2 || y1 == y2 || dx == dy);
        if (piece == "Knight") return (dx * dy == 2);
        if (piece == "King") return (dx <= 1 && dy <= 1);
        
        return false;
    }
};

int main() {
    std::cout << "Rook (0,0) to (0,5): " << (ChessValidator::isValidMove("Rook", 0, 0, 0, 5) ? "Valid" : "Invalid") << "\n";
    std::cout << "Bishop (0,0) to (2,3): " << (ChessValidator::isValidMove("Bishop", 0, 0, 2, 3) ? "Valid" : "Invalid") << "\n";
    std::cout << "Knight (0,0) to (1,2): " << (ChessValidator::isValidMove("Knight", 0, 0, 1, 2) ? "Valid" : "Invalid") << "\n";
    return 0;
}
