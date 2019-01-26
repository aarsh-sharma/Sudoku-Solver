#include <iostream>
using namespace std;

#define DIM 9
#define BLANK 0
#define SPACE " "
#define LINE "|"
#define NEW_ROW "-------------------------------"
#define GRID_FULL std::make_pair(9, 9)

// Prints the Sudoku grid
void print_grid(int grid[DIM][DIM]) {
    for (int i = 0; i < DIM; ++i) {
        cout << SPACE << SPACE << SPACE << SPACE << endl;
        // cout << NEW_ROW << endl;
        if(i % 3 == 0) {
            cout << NEW_ROW << endl;
        }
        for (int j = 0; j < DIM; ++j) {
            if (j == 0) {
                cout << LINE;
            }
            cout << SPACE;
            if (grid[i][j] == BLANK) {
                cout << SPACE;
            } else {
                cout << grid[i][j];
            }
            cout << SPACE ;
            if((j+1) % 3 == 0) {
                cout << LINE;
            }
        }
    }
    cout << endl << NEW_ROW << endl << endl;
}

// To check wheather the value is in the row
bool in_row(int grid[DIM][DIM], int row, int num) {
    for (int col = 0; col < DIM; ++col) {
        if(grid[row][col] == num) {
            return false;
        }
    }
    return true;
}

// To check wheather the value is in the column
bool in_col(int grid[DIM][DIM], int col, int num) {
    for (int row = 0; row < DIM; ++row) {
        if(grid[row][col] == num) {
            return false;
        }
    }
    return true;
}

// To check wheather the value is in the box
bool in_box(int grid[DIM][DIM], int start_row, int start_col, int num) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if(grid[start_row + row][start_col + col] == num) {
                return false;
            }
        }
    }
    return true;
}

// To check if number is valid in the given position
bool is_valid(int grid[DIM][DIM], int row, int col, int num) {
    return in_row(grid, row, num) && in_col(grid, col, num) && in_box(grid, row - row%3, col - col%3, num);
}

// Iterate through grid to find unassigned positions
bool unassigned_pos(int grid[DIM][DIM], int &row, int &col) {
    for (row = 0; row < DIM; ++row) {
        for (col = 0; col < DIM; ++col) {
            if(grid[row][col] == BLANK) {
                return false;
            }
        }
    }
    return true;
}

// This uses backtracking to solve the sudoku
bool solve_sudoku(int grid[DIM][DIM]) {
    int row, col;

    // to check whether the sudoku is completely solved
    if(unassigned_pos(grid, row, col)) {
        return true;
    }

    // considering digits from 1-9
    for (int num = 1; num <= 9; ++num) {
        if (is_valid(grid, row, col, num)) {
            grid[row][col] = num;

            if (solve_sudoku(grid)) {
                return true;
            }

            grid[row][col] = BLANK;
        }
    }
    return false; // this starts backtracking
}

int main()
{
    int grid[DIM][DIM] =    {
                                {3, 0, 6, 5, 0, 8, 4, 0, 0},
                                {5, 2, 0, 0, 0, 0, 0, 0, 0},
                                {0, 8, 7, 0, 0, 0, 0, 3, 1},
                                {0, 0, 3, 0, 1, 0, 0, 8, 0},
                                {9, 0, 0, 8, 6, 3, 0, 0, 5},
                                {0, 5, 0, 0, 9, 0, 6, 0, 0},
                                {1, 3, 0, 0, 0, 0, 2, 5, 0},
                                {0, 0, 0, 0, 0, 0, 0, 7, 4},
                                {0, 0, 5, 2, 0, 6, 3, 0, 0}
                            };
    if (solve_sudoku(grid) == true) {
        print_grid(grid);
    }
    else {
        printf("No solution exists");
    }

    return 0;
}
