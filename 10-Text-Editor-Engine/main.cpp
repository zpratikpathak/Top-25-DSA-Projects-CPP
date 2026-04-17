#include <iostream>
#include <list>
#include <stack>
#include <string>

class TextEditor {
    std::list<char> text;
    std::list<char>::iterator cursor;
    std::stack<std::string> undoStack;

public:
    TextEditor() {
        cursor = text.end();
    }

    void insert(char c) {
        text.insert(cursor, c);
        undoStack.push("insert"); // Simplification
    }

    void moveCursorLeft() {
        if (cursor != text.begin()) --cursor;
    }

    void moveCursorRight() {
        if (cursor != text.end()) ++cursor;
    }

    void backspace() {
        if (cursor != text.begin()) {
            auto it = cursor;
            --it;
            text.erase(it);
        }
    }

    void display() {
        for (auto it = text.begin(); it != text.end(); ++it) {
            if (it == cursor) std::cout << "|";
            std::cout << *it;
        }
        if (cursor == text.end()) std::cout << "|";
        std::cout << "\n";
    }
};

int main() {
    TextEditor ed;
    ed.insert('H');
    ed.insert('e');
    ed.insert('l');
    ed.insert('l');
    ed.insert('o');
    ed.display();
    ed.moveCursorLeft();
    ed.moveCursorLeft();
    ed.insert(' ');
    ed.display();
    ed.backspace();
    ed.display();
    return 0;
}
