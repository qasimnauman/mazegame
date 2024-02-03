#include <iostream>
#include "Mazer.h" 
#include "Path.h"
#include "MazeStringReader.h"
#include "BreadthFirstSearch.h"
#include "play.h"
#define animation
#ifdef animation
using namespace std;

#define speed 0.5 // lower number to increase speed. max speed is 0. 
#include "MazePrint.h"

void findPath(Maze& maze, Vertex* start, Vertex* end, MazePrint& mp)
{

    BreadthFirstSearch bfs; // Using BreadthFirstSearch directly
    bfs.findPath(start, end);
    if (bfs.getPath().empty()) {
        cout << "Path does not exist!\n";
    }

    else {

        while (!bfs.getVisted().empty()) {
            mp.animate(bfs.getVisted().front().from, bfs.getVisted().front().to, true);
            bfs.getVisted().pop();
        }

        for (auto it = ++bfs.getPath().rbegin(); it != bfs.getPath().rend(); ++it) {
            mp.animate(end, *it, false);
            end = *it;
        }
        system("cls");

        mp.printPath(bfs.getPath());
    }

}

int main() {
    Maze maze;
    MazeStringReader msb;
    MazePrint mp;
    string in;
    while (true) {
        system("CLS");


        cout << "\t\t\t\t\t///////////////////////" << endl;
        cout << "\t\t\t\t\t/        WELCOME      /" << endl;
        cout << "\t\t\t\t\t/------------------- /" << endl;
        cout << "\t\t\t\t\t/ 1: PLAY            /" << endl;
        cout << "\t\t\t\t\t/------------------- /" << endl;
        cout << "\t\t\t\t\t/ 2: LOAD MAZE       /" << endl;
        cout << "\t\t\t\t\t/-------------------/" << endl;
        cout << "\t\t\t\t\t/ 3: FIND PATH      /" << endl;
        cout << "\t\t\t\t\t/------------------- /" << endl;
        cout << "\t\t\t\t\t/ 4: EXIT            /" << endl;
        cout << "\t\t\t\t\t/------------------- /" << endl;
        cout << "\t\t\t\t\t///////////////////////" << endl;
        char option = '\0';

        switch (option = _getch()) {
        case '1':
            play();
            break;
        case '2': // Load Maze
            cout << "Enter file name: ";  cin >> in;
            while (cin.get() != '\n');  // clean line
            if (!msb.getFile(in)) break;

            maze.setMaze(msb);

            mp.setMaze(maze, msb.getText());
            mp.printAt(maze.maze_begin(), 'S');
            mp.printAt(maze.maze_end(), 'E');
            mp.printMaze();
            system("pause");
            break;
        case '3': // Find Path
            if (maze.empty()) {
                cout << "Maze not set!\n";
                break;
            }
            mp.setMaze(maze, msb.getText());
            findPath(maze, maze.maze_begin(), maze.maze_end(), mp);
            cout << '\n';
            system("pause");
            break;
        case '4': // exit
            cout << "\nGoodBye!\n";
            return 0;

        }

    }
    return 0;

}
#endif
