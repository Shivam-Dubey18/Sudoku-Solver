#include <iostream>
#include <vector>
using namespace std;

const int N = 9;

// Function to print the Sudoku board
void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

// Function to check if it's safe to place a number in a specific cell
bool isSafe(const vector<vector<int>>& board, int row, int col, int num) {
    // Check the row
    for (int x = 0; x < N; x++) {
        if (board[row][x] == num) {
            return false;
        }
    }

    // Check the column
    for (int x = 0; x < N; x++) {
        if (board[x][col] == num) {
            return false;
        }
    }

    // Check the 3x3 box
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Recursive function to solve the Sudoku
bool solveSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            // Find an empty cell
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    // Check if it's safe to place the number
                    if (isSafe(board, row, col, num)) {
                        board[row][col] = num; // Place the number

                        // Recursively try to fill in the rest of the board
                        if (solveSudoku(board)) {
                            return true;
                        }

                        // If it doesn't lead to a solution, reset and try next number
                        board[row][col] = 0;
                    }
                }
                return false; // No number can be placed, trigger backtracking
            }
        }
    }
    return true; // Solved
}

int main() {
    // Sample Sudoku puzzle (0 represents empty cells)
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(board)) {
        cout << "Solved Sudoku:\n";
        printBoard(board);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}
