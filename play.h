#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;

vector<string> maze1 = {
    "+---+--+---+---+---+---+---+--+---+--+---+---+---+---+---+---+",
    "S                                 |          |               |",
    "+  +---+---+---+---+---+---+  +   +  +---+---+   +---+   +---+",
    "|  |                          |                  |           |",
    "+  +   +---+---+   +---+   +--+---+  +---+---+---+   +---+---+",
    "|  |           |              |          |                   |",
    "+  +---+---+---+   +---+---+  +---+--+---+---+---+   +---+---+",
    "|                  |                                         |",
    "+--+---+---+---+---+---+---+--+---+  +---+---+---+---+---+---+",
    "|                                                           F|",
    "+--+---+---+---+---+---+---+--+---+--+---+---+---+---+---+---+"
};

vector<string> maze2 = {
    "+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+",
    "|S                                          |           |       |",
    "+   +---+---+---+   +---+---+   +---+---+   +   +---+---+   +   +",
    "|   |       |       |                   |   |       |       |   |",
    "+   +   +   +   +---+---+---+---+   +---+---+---+---+---+   +   +",
    "|       |   |                                               |   |",
    "+---+---+   +---+---+---+---+---+---+---+---+---+   +---+---+---+",
    "|           |                                                   |",
    "+   +   +---+---+---+---+---+   +---+---+---+---+---+---+---+---+",
    "|   |               |                               |           |",
    "+   +---+---+---+---+---+---+---+---+   +---+---+---+   +---+---+",
    "|                   |               |                           |",
    "+---+---+   +   +---+   +---+---+---+   +---+---+---+---+---+---+",
    "|           |       |                               |           |",
    "+   +---+---+---+---+---+---+---+---+   +---+---+---+---+---+---+",
    "|   |                       |                               |   |",
    "+   +   +---+---+---+---+---+---+---+   +   +---+---+---+---+   +",
    "|                                       |                      F|",
    "+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+"
};

struct Position {
    int x;
    int y;
};


void InputHandle(int& move, int& pX, int& pY, const vector<string>& maze, bool& escapePressed, int& c) {
    switch (move = _getch()) {
    case KEY_UP:
        if (pY - 1 >= 0 && maze[pY - 1][pX] != '-' && maze[pY - 1][pX] != '+' && maze[pY - 1][pX] != '|') {
            pY--;
            c++;
        }
        break;
    case KEY_DOWN:
        if (pY + 1 < maze.size() && maze[pY + 1][pX] != '-' && maze[pY + 1][pX] != '+' && maze[pY + 1][pX] != '|') {
            pY++;
            c++;
        }
        break;
    case KEY_RIGHT:
        if (pX + 1 < maze[pY].size() && maze[pY][pX + 1] != '-' && maze[pY][pX + 1] != '+' && maze[pY][pX + 1] != '|') {
            pX++;
            c++;
        }
        break;
    case KEY_LEFT:
        if (pX - 1 >= 0 && maze[pY][pX - 1] != '-' && maze[pY][pX - 1] != '+' && maze[pY][pX - 1] != '|') {
            pX--;
            c++;
        }
        break;
    case 27: // Escape key
        escapePressed = true;
        break;
    }
}

void Display(int pX, int pY, const vector<string>& maze) {
    for (size_t i = 0; i < maze.size(); ++i) {
        for (size_t j = 0; j < maze[i].size(); ++j) {
            if (j == pX && i == pY) {

                cout << "P ";
            }
            else {

                cout << maze[i][j] << " ";
            }
        }
        cout << "\n";
    }
}

void DisplayMaze(int playerPosX, int playerPosY, const vector<string>& maze, int c) {
    system("CLS");
    cout << "Total Moves: " << c << endl;
    Display(playerPosX, playerPosY, maze);
}
bool CheckWinCondition(int pX, int pY, const vector<string>& maze) {
    return (maze[pY][pX] == 'F');
}

void play() {
    char choice = '\0';
    while (choice != '0') {
        int playerPosX = 0;
        int playerPosY = 1;
        int movement;
        bool escapePressed = false;

        cout << endl;

        system("CLS");
        cout << "\t\t\t\t\t///////////////////////" << endl;
        cout << "\t\t\t\t\t/        GAME         /" << endl;
        cout << "\t\t\t\t\t/------------------- /" << endl;
        cout << "\t\t\t\t\t/ 1: FIRST MAP       /" << endl;
        cout << "\t\t\t\t\t/------------------- /" << endl;
        cout << "\t\t\t\t\t/ 2: SECOND MAP      /" << endl;
        cout << "\t\t\t\t\t/------------------- /" << endl;
        cout << "\t\t\t\t\t/ 0: EXIT            /" << endl;
        cout << "\t\t\t\t\t/------------------- /" << endl;
        cout << "\t\t\t\t\t///////////////////////" << endl;

        switch (choice = _getch()) {
        case '1':
        case '2': {
            const vector<string>& selectedMaze = (choice == '1') ? maze1 : maze2;
            int count = 0;
            DisplayMaze(playerPosX, playerPosY, selectedMaze, count);
            while (!CheckWinCondition(playerPosX, playerPosY, selectedMaze) && !escapePressed) {
                InputHandle(movement, playerPosX, playerPosY, selectedMaze, escapePressed, count);
                system("CLS");


                DisplayMaze(playerPosX, playerPosY, selectedMaze, count);
            }
            if (!escapePressed) {

                cout << "Congratulations! You finished the maze!\n";
            }
            else {
                cout << "Game terminated by the user!\n";
            }
            break;
        }
        case '0': {

            cout << "Exiting" << endl;
            break;
        }
        default: {

            cout << "Invalid Option" << endl;
            continue;
        }
        }
    }
}