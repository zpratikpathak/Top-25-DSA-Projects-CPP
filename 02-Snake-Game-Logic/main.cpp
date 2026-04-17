#include <iostream>
#include <vector>
#include <deque>

struct Point {
    int x, y;
};

class SnakeGame {
    int width, height;
    std::deque<Point> snake;
    Point food;
    bool gameOver;

public:
    SnakeGame(int w, int h) : width(w), height(h), gameOver(false) {
        snake.push_front({w / 2, h / 2});
        food = {rand() % w, rand() % h};
    }

    void move(char direction) {
        if (gameOver) return;

        Point head = snake.front();
        if (direction == 'W') head.y--;
        if (direction == 'S') head.y++;
        if (direction == 'A') head.x--;
        if (direction == 'D') head.x++;

        // Logic for collision or eating
        if (head.x == food.x && head.y == food.y) {
            std::cout << "Food consumed!\n";
            food = {rand() % width, rand() % height};
        } else {
            snake.pop_back();
        }

        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height) {
            gameOver = true;
            std::cout << "Wall Collision! Game Over.\n";
            return;
        }

        snake.push_front(head);
    }

    void status() {
        std::cout << "Snake Length: " << snake.size() << " | Head: (" << snake.front().x << ", " << snake.front().y << ")\n";
    }
};

int main() {
    SnakeGame game(20, 20);
    game.status();
    game.move('W');
    game.move('D');
    game.status();
    return 0;
}
