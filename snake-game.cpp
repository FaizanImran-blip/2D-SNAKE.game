#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
using namespace std;

enum Direction { stop = 0, left, right, up, down };
Direction dir;

const int width = 20;
const int height = 20;

int headX, headY, fruitX, fruitY, score;
int tailX[100], tailY[100], tailLength;
bool gameOver;

void setup();
void draw();
void input();
void logic();

int main() {
    srand(time(0));
    cout << "|--------------------------------|\n";
    cout << ":::::::::::: SNAKE GAME ::::::::::\n";
    cout << "|--------------------------------|\n";
    cout << "-- Press any key to start the game --\n";
    getch();

    setup();

    while (!gameOver) {
        draw();
        input();
        logic();

        int speed = 100 - (score / 10);
        if (speed < 30) speed = 30;
        Sleep(speed);
    }

    system("cls");
    cout << "\n\n\t\tGAME OVER!\n";
    cout << "\t\tFinal Score: " << score << "\n";
    cout << "\t\tPress any key to exit...\n";
    getch();

    return 0;
}

void setup() {
    dir = stop;
    gameOver = false;
    headX = width / 2;
    headY = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    tailLength = 0;
}

void draw() {
    system("cls");

    cout << "\t\t";
    for (int i = 0; i < width; i++) cout << "==";
    cout << endl;

    for (int i = 0; i < height; i++) {
        cout << "\t\t||";
        for (int j = 0; j < width; j++) {
            if (i == headY && j == headX)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "*";
            else {
                bool printTail = false;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        printTail = true;
                        break;
                    }
                }
                if (!printTail) cout << " ";
            }
        }
        cout << "||" << endl;
    }

    cout << "\t\t";
    for (int i = 0; i < width; i++) cout << "==";
    cout << "\n\n\t\t\tScore: [" << score << "]\n";
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                if (dir != right) dir = left;
                break;
            case 'd':
                if (dir != left) dir = right;
                break;
            case 'w':
                if (dir != down) dir = up;
                break;
            case 's':
                if (dir != up) dir = down;
                break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int tempX, tempY;

    tailX[0] = headX;
    tailY[0] = headY;

    for (int i = 1; i < tailLength; i++) {
        tempX = tailX[i];
        tempY = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }

    switch (dir) {
        case left:  headX--; break;
        case right: headX++; break;
        case up:    headY--; break;
        case down:  headY++; break;
        default: break;
    }

    if (headX >= width) headX = 0;
    else if (headX < 0) headX = width - 1;

    if (headY >= height) headY = 0;
    else if (headY < 0) headY = height - 1;

    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == headX && tailY[i] == headY)
            gameOver = true;
    }

    if (headX == fruitX && headY == fruitY) {
        score += 10;
        tailLength++;

        while (true) {
            fruitX = rand() % width;
            fruitY = rand() % height;
            bool valid = true;

            if (fruitX == headX && fruitY == headY) {
                valid = false;
            } else {
                for (int i = 0; i < tailLength; i++) {
                    if (tailX[i] == fruitX && tailY[i] == fruitY) {
                        valid = false;
                        break;
                    }
                }
            }

            if (valid) break;
        }
    }
}
