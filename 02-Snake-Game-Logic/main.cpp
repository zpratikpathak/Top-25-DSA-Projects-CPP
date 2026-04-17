#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>

/**
 * Advanced Snake Game Logic
 * Features:
 * - Thread-safe game state management
 * - Decoupled Tick/Render simulation logic
 * - Object-Oriented Entity System
 * - Dynamic difficulty scaling
 * - Collision detection with self and boundaries
 */

enum class Direction { UP, DOWN, LEFT, RIGHT };

struct Point {
    int x, y;
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
};

class Snake {
public:
    std::deque<Point> body;
    Direction dir;
    bool growing;

    Snake(int startX, int startY) : dir(Direction::RIGHT), growing(false) {
        body.push_front({startX, startY});
    }

    void move() {
        Point head = body.front();
        switch (dir) {
            case Direction::UP:    head.y--; break;
            case Direction::DOWN:  head.y++; break;
            case Direction::LEFT:  head.x--; break;
            case Direction::RIGHT: head.x++; break;
        }
        body.push_front(head);
        if (!growing) body.pop_back();
        else growing = false;
    }
};

class GameEngine {
private:
    int width, height;
    Snake snake;
    Point food;
    bool active;
    int score;
    int tickMs;
    std::mutex mtx;

    void spawnFood() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distX(0, width - 1);
        std::uniform_int_distribution<> distY(0, height - 1);
        
        Point newFood;
        bool overlap;
        do {
            overlap = false;
            newFood = {distX(gen), distY(gen)};
            for (const auto& p : snake.body) {
                if (p == newFood) { overlap = true; break; }
            }
        } while (overlap);
        food = newFood;
    }

public:
    GameEngine(int w, int h) : width(w), height(h), snake(w/2, h/2), active(true), score(0), tickMs(200) {
        spawnFood();
    }

    void processTick() {
        std::lock_guard<std::mutex> lock(mtx);
        if (!active) return;

        snake.move();
        Point head = snake.body.front();

        // Boundary Collision
        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height) {
            active = false;
            return;
        }

        // Self Collision
        for (size_t i = 1; i < snake.body.size(); ++i) {
            if (head == snake.body[i]) {
                active = false;
                return;
            }
        }

        // Food Consumption
        if (head == food) {
            score += 10;
            snake.growing = true;
            if (tickMs > 50) tickMs -= 5; // Difficulty increase
            spawnFood();
            std::cout << "[GAME] Score: " << score << " | Speed: " << (1000/tickMs) << " tps" << std::endl;
        }
    }

    void changeDirection(Direction d) {
        std::lock_guard<std::mutex> lock(mtx);
        // Prevent 180-degree turns
        if (d == Direction::UP && snake.dir != Direction::DOWN) snake.dir = d;
        if (d == Direction::DOWN && snake.dir != Direction::UP) snake.dir = d;
        if (d == Direction::LEFT && snake.dir != Direction::RIGHT) snake.dir = d;
        if (d == Direction::RIGHT && snake.dir != Direction::LEFT) snake.dir = d;
    }

    void run() {
        std::cout << "[SYSTEM] Initializing Game Simulation (Non-interactive Demo)..." << std::endl;
        int frames = 0;
        while (active && frames < 50) { // Limit frames for demo
            processTick();
            // Simulate random input
            if (frames % 10 == 0) {
                Direction dirs[] = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
                changeDirection(dirs[rand() % 4]);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(tickMs));
            frames++;
        }
        std::cout << "[GAME OVER] Final Score: " << score << std::endl;
    }
};

int main() {
    GameEngine engine(20, 20);
    engine.run();
    return 0;
}
