#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>

using namespace std;

/* Reads file and creates a boolean grid based on file content. The fileName is the resource file to be read. */
void fileToGrid(string fileName, Grid<bool> &board);

/* Prints the grid to the console. */
void printGrid(Grid<bool> &board);

/* Advances the grid one generation according to the rules of Conway's Game of Life.*/
void advanceGrid(Grid<bool> &board);

/* Animates the grid n generations. */
void animateGrid(int n, Grid<bool> &board);

int main() {
    bool run = true;
    string nKey;
    string fileName;

    cout << "Welcome to the TDDD86 Game of Life, " << endl <<
            "a simulation of the lifecycle of a bacteria colony." << endl <<
            "Cells (X) live and die by the following rules:" << endl <<
            "- A cell with 1 or fewer neighbours dies." << endl <<
            "- Locations with 2 neighbours remain stable." << endl <<
            "- Locations with 3 neighbours will create life." << endl <<
            "- A cell with 4 or more neighbours dies." << endl;

    cout << "Grid input file name? ";
    cin >> fileName;

    Grid<bool> board;
    fileToGrid(fileName, board);

    while(run){
        clearConsole();
        printGrid(board);

        cout << "a)nimate, t)ick, q)uit? " << endl;
        cin >> nKey;

        if (nKey == "a"){
            animateGrid(40, board);
        }

        else if(nKey == "t"){
            advanceGrid(board);
        }
        else if (nKey == "q") {
            run = false;
        }
    }

    cout << "Have a nice Life!" << endl;
    return 0;
}

void animateGrid(int n, Grid<bool> &board){
    int delay = 100;

    for(int i = 0; i < n; i++){
        clearConsole();
        advanceGrid(board);
        printGrid(board);
        pause(delay);
    }
}


void fileToGrid(string fileName, Grid<bool> &board){
    int rows;
    int cols;

    ifstream input;
    input.open(fileName);
    string line;

    input >> rows;
    input >> cols;

    board.resize(rows, cols);

    for(int i = 0; i < rows; i++){

        input >> line;

        for(int j = 0; j < cols; j++){
            board.set(i, j, (line[j] == 'X'));
        }
    }

    input.close();
}


void printGrid(Grid<bool> &board){
    for(int i = 0; i < board.numRows(); i++){
        for(int j = 0; j < board.numCols(); j++){
            if(board.get(i, j)){
                cout << "X";
            }
            else{
                cout << "-";
            }
        }
        cout << endl;
    }
}

void advanceGrid(Grid<bool> &board){
    int cols = board.numCols();
    int rows = board.numRows();

    Grid<bool> newBoard (rows, cols);

    int neighborCount = 8;

    //Array of delta to all the neighbors that should be counted.
    int neighborCords[][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            int alive = 0;

            //Iterate over neighbor deltas
            for(int k = 0; k < neighborCount; k++){
                int neighborRow = i + neighborCords[k][0];
                int neighborCol = j + neighborCords[k][1];

                if(board.inBounds(neighborRow, neighborCol) && board.get(neighborRow, neighborCol)){
                    alive++;
                }
            }

            //set new cell
            if(alive < 2){
                newBoard.set(i, j, false);
            }
            else if(alive == 2){
                newBoard.set(i, j, board.get(i, j));
            }
            else if(alive == 3){
                newBoard.set(i, j, true);
            }
            else{
                newBoard.set(i, j, false);
            }
        }
    }

    board = newBoard;
}
