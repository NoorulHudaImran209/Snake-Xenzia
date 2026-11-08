#include <iostream>
#include <windows.h>
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

const int ROWS = 24, COLS = 84;
char maze[ROWS][COLS];
int score = 0, lives = 3, level = 1;
int snakeX[400], snakeY[400], snakeLength = 6;
int directionX = 0, directionY = 1, speedDelay = 150;
int foodIndex = 0;

int foodPos[5][2] = {
    {5, 10}, {10, 25}, {15, 45}, {18, 55}, {7, 70}
};

bool showLevelUp = false;
int levelMessageTimer = 0;

void setColor(int color) {
    SetConsoleTextAttribute(h, color);
}

void drawMazeBase();
void drawWalls();
void inputHandler();
void moveSnake();
void updateMaze();
void placeFood();
void printMaze();
void checkCollision();
void increaseLevel();
void gameOverScreen();
void showScorePanel();

int main() {
    drawMazeBase();
    drawWalls();
    placeFood();

    for (int i = 0; i < snakeLength; i++) {
        snakeX[i] = 12;
        snakeY[i] = 13 - i;
    }

    while (lives > 0) {
        Sleep(speedDelay);
        inputHandler();
        moveSnake();
        checkCollision();
        if (lives <= 0) break;

        drawMazeBase();
        drawWalls();
        placeFood();
        updateMaze();

        system("CLS");
        printMaze();
        showScorePanel();

        if (showLevelUp) {
            cout << " " << endl;
            setColor(13);
            cout << "                               *** LEVEL " << level << " UNLOCKED! ***" << endl;
            setColor(7);
            levelMessageTimer++;
            if (levelMessageTimer >= 10) {
                showLevelUp = false;
                levelMessageTimer = 0;
            }
        }
    }
    gameOverScreen();
    return 0;
}

void drawMazeBase() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (r == 0 || r == ROWS - 1 || c == 0 || c == COLS - 2)
                maze[r][c] = '*';
            else
                maze[r][c] = ' ';
        }
    }
}

void drawWalls() {
    for (int r = 6; r < 18; r++) {
        maze[r][20] = '|';
        maze[r][60] = '%';
    }
}

void printMaze() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            char ch = maze[r][c];
            if (ch == '*') {
                setColor(12);
                cout << "*#*";
                c += 2;
            } else if (ch == '|' || ch == '%') {
                setColor(9);
                cout << ch;
            } else if (ch == 'O') {
                setColor(14);
                cout << 'O';
            } else if (ch == 'o') {
                setColor(6);
                cout << 'o';
            } else if (ch == '&') {
                setColor(10);
                cout << '&';
            } else {
                setColor(7);
                cout << ' ';
            }
        }
        cout << endl;
    }
}

void inputHandler() {
    // Using & instead of &x8000 as per your request
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        directionX = -1; directionY = 0;
    } else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        directionX = 1; directionY = 0;
    } else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        directionX = 0; directionY = -1;
    } else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        directionX = 0; directionY = 1;
    }
}

void moveSnake() {
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    snakeX[0] += directionX;
    snakeY[0] += directionY;

    if (snakeX[0] <= 0)
        snakeX[0] = ROWS - 2;
    if (snakeX[0] >= ROWS - 1)
        snakeX[0] = 1;
    if (snakeY[0] <= 0)
        snakeY[0] = COLS - 3;
    if (snakeY[0] >= COLS - 2)
        snakeY[0] = 1;
}

void placeFood() {
    int fx = foodPos[foodIndex][0];
    int fy = foodPos[foodIndex][1];
    maze[fx][fy] = '&';  // Only one '&' instead of a 2x2 square as requested
}

void updateMaze() {
    for (int r = 1; r < ROWS - 1; r++) {
        for (int c = 1; c < COLS - 2; c++) {
            if (maze[r][c] == 'O' || maze[r][c] == 'o')
                maze[r][c] = ' ';
        }
    }

    for (int i = 0; i < snakeLength; i++) {
        if (i == 0) {
            maze[snakeX[i]][snakeY[i]] = 'O';
        } else {
            maze[snakeX[i]][snakeY[i]] = 'o';
        }
    }
}

void checkCollision() {
    int headX = snakeX[0], headY = snakeY[0];

    if (maze[headX][headY] == '&') {
        score += 50;
        foodIndex = (foodIndex + 1) % 5;

        for (int k = 0; k < 5; k++) {
            snakeX[snakeLength] = snakeX[snakeLength - 1];
            snakeY[snakeLength] = snakeY[snakeLength - 1];
            snakeLength++;
        }

        if (score == 200 || score == 400)
            increaseLevel();
    } else if (maze[headX][headY] == '|' || maze[headX][headY] == '%' || maze[headX][headY] == 'o') {
        lives--;
        snakeLength = 6;
        for (int i = 0; i < 6; i++) {
            snakeX[i] = 12;
            snakeY[i] = 13 - i;
        }
        directionX = 0; directionY = 1;
    }
}

void increaseLevel() {
    level++;
    showLevelUp = true;
    if (level == 2) speedDelay = 100;
    if (level == 3) speedDelay = 60;
}

void gameOverScreen() {
    system("CLS");
    setColor(12);
    cout << endl << endl << endl;
    cout << "\t\t\t=====================" << endl;
    cout << "\t\t\t      GAME OVER      " << endl;
    cout << "\t\t\t=====================" << endl << endl;
    setColor(14);
    cout << "\t\t\tFinal Score: " << score << endl;
    setColor(7);
}

void showScorePanel() {
    cout << " " << endl;
    setColor(14);
    cout << "Score: " << score << "   ";
    setColor(11);
    cout << "                           Lives: " << lives << "   ";
    setColor(14);
    cout << "                             Level: " << level << endl;
    setColor(7);
}
