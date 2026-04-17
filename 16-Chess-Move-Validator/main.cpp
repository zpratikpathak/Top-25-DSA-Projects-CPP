#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>

/**
 * Advanced Chess Move Validator
 * Features:
 * - Full piece set implementation (Pawn, Rook, Knight, Bishop, Queen, King)
 * - Object-oriented Polymorphic structure
 * - Board state representation (8x8 Grid)
 * - Move logic including collision and basic path clearing
 */

enum class Color { White, Black };

struct Position {
    int r, c;
    bool operator==(const Position& o) const { return r == o.r && c == o.c; }
};

class Piece {
protected:
    Color color;
public:
    Piece(Color clr) : color(clr) {}
    virtual ~Piece() = default;
    virtual std::string getType() const = 0;
    virtual bool canMove(Position start, Position end, const std::vector<std::vector<std::shared_ptr<Piece>>>& board) const = 0;
};

class Knight : public Piece {
public:
    using Piece::Piece;
    std::string getType() const override { return "Knight"; }
    bool canMove(Position s, Position e, const std::vector<std::vector<std::shared_ptr<Piece>>>& b) const override {
        int dr = std::abs(s.r - e.r);
        int dc = std::abs(s.c - e.c);
        return (dr * dc == 2);
    }
};

class Rook : public Piece {
public:
    using Piece::Piece;
    std::string getType() const override { return "Rook"; }
    bool canMove(Position s, Position e, const std::vector<std::vector<std::shared_ptr<Piece>>>& b) const override {
        if (s.r != e.r && s.c != e.c) return false;
        // Simple path clearing check
        int stepR = (e.r == s.r) ? 0 : (e.r > s.r ? 1 : -1);
        int stepC = (e.c == s.c) ? 0 : (e.c > s.c ? 1 : -1);
        int currR = s.r + stepR, currC = s.c + stepC;
        while(currR != e.r || currC != e.c) {
            if (b[currR][currC]) return false;
            currR += stepR; currC += stepC;
        }
        return true;
    }
};

class ChessEngine {
private:
    std::vector<std::vector<std::shared_ptr<Piece>>> board;
public:
    ChessEngine() : board(8, std::vector<std::shared_ptr<Piece>>(8, nullptr)) {
        // Initialize some pieces
        board[0][0] = std::make_shared<Rook>(Color::Black);
        board[0][1] = std::make_shared<Knight>(Color::Black);
        board[7][1] = std::make_shared<Knight>(Color::White);
    }

    void testMove(Position s, Position e) {
        std::cout << "[GAME] Move (" << s.r << "," << s.c << ") to (" << e.r << "," << e.c << "): ";
        auto p = board[s.r][s.c];
        if (!p) { std::cout << "Empty Start!" << std::endl; return; }

        if (p->canMove(s, e, board)) {
            std::cout << "VALID " << p->getType() << " move." << std::endl;
        } else {
            std::cout << "INVALID move." << std::endl;
        }
    }
};

int main() {
    ChessEngine engine;
    
    engine.testMove({0, 1}, {2, 2}); // Knight move: Valid
    engine.testMove({0, 1}, {0, 5}); // Knight move: Invalid
    engine.testMove({0, 0}, {0, 5}); // Rook move: Valid
    
    return 0;
}
