#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 20, height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100], tailLength;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2; // Start snake in the middle
    y = height / 2;
    fruitX = rand() % width; // Random fruit position
    fruitY = rand() % height;
    score = 0;
    tailLength = 0;
}

void Draw() {
    system("cls"); // Clear console
    // Draw top wall
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;
    
    // Draw game board
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#"; // Left wall
            if (i == y && j == x) cout << "O"; // Snake head
            else if (i == fruitY && j == fruitX) cout << "F"; // Fruit
            else {
                bool isTail = false;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Snake tail
                        isTail = true;
                    }
                }
                if (!isTail) cout << " ";
            }
            if (j == width - 1) cout << "#"; // Right wall
        }
        cout << endl;
    }
    
    // Draw bottom wall
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << "\nScore: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': if (dir != RIGHT) dir = LEFT; break;
            case 'd': if (dir != LEFT) dir = RIGHT; break;
            case 'w': if (dir != DOWN) dir = UP; break;
            case 's': if (dir != UP) dir = DOWN; break;
            case 'x': gameOver = true; break; // Exit game
        }
    }
}

void Logic() {
    // Store previous head position
    int prevX = tailX[0], prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    int prev2X, prev2Y;
    
    // Update tail positions
    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    
    // Move snake head
    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
    }
    
    // Wrap around edges
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
    
    // Check collision with tail
    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }
    
    // Check if snake eats fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tailLength++;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // Slow down game
    }
    cout << "Game Over! Final Score: " << score << endl;
    return 0;
}