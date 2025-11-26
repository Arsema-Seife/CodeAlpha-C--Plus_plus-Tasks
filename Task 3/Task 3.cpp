#include <iostream>
#include <sstream>
using namespace std;

// Function to print Sudoku grid
void printGrid(int grid[9][9]) {
    cout << "\n-------------------\n";
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (grid[row][col] == 0)
                cout << ". ";
            else
                cout << grid[row][col] << " ";
        }
        cout << "|\n";
        if ((row + 1) % 3 == 0)
            cout << "-------------------\n";
    }
}

// Check if num is safe to place
bool isSafe(int grid[9][9], int row, int col, int num) {
    for (int x = 0; x < 9; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Solve Sudoku using backtracking
bool solveSudoku(int grid[9][9]) {
    int row, col;
    bool empty = false;
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (grid[row][col] == 0) {
                empty = true;
                break;
            }
        }
        if (empty) break;
    }

    if (!empty)
        return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid))
                return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

int main() {
    string choice;
    while (true) { // run indefinitely
        cout << "\n===== SUDOKU SOLVER =====\n";
        cout << "1. Solve a Sudoku\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";
        getline(cin, choice);

        if (choice == "2") {
            cout << "Exiting... Goodbye!\n";
            break;
        }
        else if (choice == "1") {
            int grid[9][9] = {0};
            string line;
            cout << "Enter Sudoku grid row by row (use 0 for empty cells, separate numbers with spaces):\n";

            for (int i = 0; i < 9; i++) {
                cout << "Row " << i + 1 << ": ";
                getline(cin, line);
                istringstream iss(line);
                for (int j = 0; j < 9; j++) {
                    if (!(iss >> grid[i][j]) || grid[i][j] < 0 || grid[i][j] > 9) {
                        cout << "Invalid input! Please enter 9 numbers between 0 and 9.\n";
                        i--; // redo this row
                        break;
                    }
                }
                printGrid(grid); // optional: show grid after each row
            }

            cout << "\nSolving Sudoku...\n";
            if (solveSudoku(grid)) {
                cout << "\nSolved Sudoku:\n";
                printGrid(grid);
            } else {
                cout << "\nNo solution exists.\n";
            }
        }
        else {
            cout << "Invalid choice. Please select 1 or 2.\n";
        }
    }

    return 0;
}
