#include <iostream>
#include <vector>
#include <tuple>
#include <cmath> 
#include <chrono>
using namespace std;
using namespace std::chrono;

// Function to print the best guess
void printGuess(const std::tuple<std::pair<int, int>, std::vector<int>>& guess) {
    cout << "----------------------------------------------------\n";
    cout << "Best Guess Position: (" << get<0>(guess).first << "," << get<0>(guess).second << ")\n";
    cout << "Best Guess num prediction: " << get<1>(guess).size() << "\n";
    cout << "Best Guess Score: " << get<1>(guess)[0] << "\n";
    cout << "----------------------------------------------------\n";
}

// Function to print the Sudoku board nicely
void printBoard(const vector<vector<int>>& board) {
    int sizeB = board.size();
    int boxSize = sqrt(sizeB);

    cout << string(sizeB * 2 + boxSize + 3, '-') << "\n"; // Dynamic separator
    for (int i = 0; i < sizeB; i++) {
        for (int j = 0; j < sizeB; j++) {
            if (j % boxSize == 0) cout << "| ";
            if (board[i][j] == 0)
                cout << ". ";
            else
                cout << board[i][j] << " ";
        }
        cout << "|\n";
        if ((i + 1) % boxSize == 0) 
            cout << string(sizeB * 2 + boxSize + 3, '-') << "\n";
    }
}

// Function to check if placing `num` at (row, col) is safe
bool isSafe(vector<vector<int>>& board, int row, int col, int num) {
    int sizeB = board.size();
    int boxSize = sqrt(sizeB); 

    for (int x = 0; x < sizeB; x++) {
        if (board[row][x] == num || board[x][col] == num)
            return false;
    }

    int startRow = row - row % boxSize, startCol = col - col % boxSize;
    for (int i = 0; i < boxSize; i++)
        for (int j = 0; j < boxSize; j++)
            if (board[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Function to find the best guess (least number of possible values)
std::tuple<std::pair<int, int>, std::vector<int>> best_pair(vector<vector<int>>& board){
    int sizeB = board.size();
    pair<int, int> bestIndex = {-1, -1};
    int  bestPredictions = sizeB + 1; // Max predictions is sizeB
    vector<int> bestValues;

    for (int i = 0; i < sizeB; i++) {
        for (int j = 0; j < sizeB; j++) {
            if (board[i][j] == 0) { // Empty cell
                vector<int> possibleValues;
                for (int num = 1; num <= sizeB; num++) {
                    if (isSafe(board, i, j, num)) {
                        possibleValues.push_back(num);
                    }
                }
                int predictions = possibleValues.size();
                if (predictions==0){
                    return {{-5, -5}, possibleValues}; // No solution
                }
                if (predictions > 0 && predictions < bestPredictions) {
                    bestPredictions = predictions;
                    bestIndex = {i, j};
                    bestValues= possibleValues;
                }
            }
        }
    }

    return {bestIndex, bestValues}; // (Position, Number, Possibilities)
}

bool solveSudoku(vector<vector<int>>& board) {
    auto [pos, candidates] = best_pair(board);

    if (pos.first == -1) return true; // No empty cells left, puzzle solved

    for (int num : candidates) { // Try each valid number
        board[pos.first][pos.second] = num;
        if (solveSudoku(board)) return true; // If this choice leads to a solution, return true
        board[pos.first][pos.second] = 0; // Otherwise, backtrack
    }

    return false; // No solution found with current choices
}


int main() {
    auto start = high_resolution_clock::now();

    // Example 9x9 Sudoku board
vector<vector<int>> board = {
    {8, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 3, 6, 0, 0, 0, 0, 0},
    {0, 7, 0, 0, 9, 0, 2, 0, 0},
    {0, 5, 0, 0, 0, 7, 0, 0, 0},
    {0, 0, 0, 0, 4, 5, 7, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 3, 0},
    {0, 0, 1, 0, 0, 0, 0, 6, 8},
    {0, 0, 8, 5, 0, 0, 0, 1, 0},
    {0, 9, 0, 0, 0, 0, 4, 0, 0}
};
    cout << "Initial Sudoku Board:\n";
    printBoard(board);
    solveSudoku(board);
    cout << "Final Sudoku Board:\n";
    printBoard(board);
    
    auto stop = high_resolution_clock::now();
    // Calculate duration
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " ms" << endl;
    return 0;
}
