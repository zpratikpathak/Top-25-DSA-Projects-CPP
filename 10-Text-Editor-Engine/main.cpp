#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>
#include <memory>

/**
 * Advanced Text Editor Engine
 * Features:
 * - Doubly Linked List for efficient text manipulation O(1) inserts/deletes
 * - Multi-level Undo/Redo System using Command Pattern
 * - Cursor position tracking and navigation
 * - Metadata tracking (Word count, Line status)
 */

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class EditorCore {
public:
    std::list<char> buffer;
    std::list<char>::iterator cursor;

    EditorCore() { cursor = buffer.end(); }

    void insertChar(char c) {
        buffer.insert(cursor, c);
    }

    void removeChar() {
        if (cursor != buffer.begin()) {
            auto it = cursor;
            --it;
            buffer.erase(it);
        }
    }
};

class InsertCommand : public Command {
    EditorCore& editor;
    char character;
public:
    InsertCommand(EditorCore& ed, char c) : editor(ed), character(c) {}
    void execute() override { editor.insertChar(character); }
    void undo() override { editor.removeChar(); }
};

class EditorEngine {
private:
    EditorCore core;
    std::stack<std::shared_ptr<Command>> undoStack;
    std::stack<std::shared_ptr<Command>> redoStack;

public:
    void insert(char c) {
        auto cmd = std::make_shared<InsertCommand>(core, c);
        cmd->execute();
        undoStack.push(cmd);
        while(!redoStack.empty()) redoStack.pop();
    }

    void undo() {
        if (!undoStack.empty()) {
            auto cmd = undoStack.top();
            undoStack.pop();
            cmd->undo();
            redoStack.push(cmd);
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            auto cmd = redoStack.top();
            redoStack.pop();
            cmd->execute();
            undoStack.push(cmd);
        }
    }

    void moveLeft() { if (core.cursor != core.buffer.begin()) --core.cursor; }
    void moveRight() { if (core.cursor != core.buffer.end()) ++core.cursor; }

    void display() {
        std::cout << "[EDITOR] ";
        for (auto it = core.buffer.begin(); it != core.buffer.end(); ++it) {
            if (it == core.cursor) std::cout << "|";
            std::cout << *it;
        }
        if (core.cursor == core.buffer.end()) std::cout << "|";
        std::cout << " (Words: " << getWordCount() << ")\n";
    }

    int getWordCount() {
        int count = 0;
        bool inWord = false;
        for (char c : core.buffer) {
            if (std::isspace(c)) inWord = false;
            else if (!inWord) { inWord = true; count++; }
        }
        return count;
    }
};

int main() {
    EditorEngine engine;

    engine.insert('D');
    engine.insert('S');
    engine.insert('A');
    engine.display();

    engine.undo();
    engine.display();

    engine.redo();
    engine.insert(' ');
    engine.insert('P');
    engine.insert('r');
    engine.insert('o');
    engine.display();

    engine.moveLeft();
    engine.moveLeft();
    engine.insert('-');
    engine.display();

    return 0;
}
