# Sudoku Solver with Backtracking and Heuristic

This C++ program solves a Sudoku puzzle using the backtracking algorithm enhanced with a heuristic to improve performance. The heuristic selects the next cell with the fewest possible valid numbers (minimum remaining values), reducing the branching factor and speeding up the solution process.

## Features

- **Backtracking Algorithm**: Utilizes backtracking to explore potential solutions and find the correct one.
- **Heuristic Search**: The solver uses the "minimum remaining values" heuristic to choose the next cell with the least number of valid numbers.
- **Formatted Output**: Displays the Sudoku board in a visually structured format, making it easy to track the board state.
- **Execution Time Measurement**: The time taken to solve the puzzle is calculated and displayed in milliseconds.

## Functions

### `printGuess`
Prints the best guess in terms of position and possible predictions for a given cell.

### `printBoard`
Displays the current Sudoku board in a grid format, separating boxes for better visualization.

### `isSafe`
Checks whether placing a number at a specific position (row, column) is valid according to Sudoku rules.

### `best_pair`
Finds the best cell to fill next based on the heuristic of minimum remaining values. Returns the cell position and its valid number candidates.

### `solveSudoku`
Solves the Sudoku board using backtracking. It fills the empty cells one by one, making guesses based on the heuristic and backtracking when necessary.

## Example Sudoku Board

The program includes an example 9x9 Sudoku puzzle in the `main` function:

```cpp
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
