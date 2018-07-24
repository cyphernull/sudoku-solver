#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
#define LENGTH 9
#define BLANK_SPACE " "
#define LINE_BETWEEN_NUM "|"
#define LINE_BETWEEN_ROW "------------------------------------"
#define COMPLETED make_pair(9, 9)
void print(int grid[LENGTH][LENGTH]) {
    for (int i = 0; i < LENGTH; i++) {
        cout << BLANK_SPACE << BLANK_SPACE << BLANK_SPACE << BLANK_SPACE << endl;
        cout << LINE_BETWEEN_ROW << endl;
        for (int j = 0; j < LENGTH; j++) {
            cout << BLANK_SPACE;
            if (grid[i][j] == 0) {
                cout << BLANK_SPACE;
            } else {
                cout << grid[i][j];
            }
            cout << BLANK_SPACE;
            cout << LINE_BETWEEN_NUM;
        }
    }
    cout << endl << LINE_BETWEEN_ROW << endl << endl;;
}
bool alreadyInSubgrid(int grid[LENGTH][LENGTH], int startRow, int startCol, int num) {
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + startRow][col + startCol] == num) {
                return true;
            }
    return false;
}
bool alreadyInRow(int grid[LENGTH][LENGTH], int row, int num) {
    for (int col = 0; col < LENGTH; col++)
        if (grid[row][col] == num) {
            return true;
        }
    return false;
}
bool alreadyInCol(int grid[LENGTH][LENGTH], int col, int num) {
    for (int row = 0; row < LENGTH; row++)
        if (grid[row][col] == num) {
            return true;
        }
    return false;
}
bool isValid(int grid[LENGTH][LENGTH], int row, int col, int num) {
    return !alreadyInRow(grid, row, num) &&
           !alreadyInCol(grid, col, num) &&
           !alreadyInSubgrid(grid, row - row % 3, col - col % 3, num);
}

pair<int, int> getUnusedLocation(int grid[LENGTH][LENGTH]) {
    for (int row = 0; row < LENGTH; row++)
        for (int col = 0; col < LENGTH; col++)
            if (grid[row][col] == 0) {
                return make_pair(row, col);
            }
    return COMPLETED;
}
bool solve(int grid[LENGTH][LENGTH]) {
    if (getUnusedLocation(grid) == COMPLETED) {
        return true;
    }
    pair<int, int> position = getUnusedLocation(grid);
    int row = position.first;
    int col = position.second;
    for (int num = 1; num <= 9; num++) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;
            if (solve(grid)) {
                return true;
            }
            grid[row][col] = 0;
        }
    }
    return false;
}
int main() {
    cout << "Sodoku" << endl;

    int grid[LENGTH][LENGTH] = {{5, 3, 0, 0, 7, 0, 0, 0, 0},
                                {6, 0, 0, 1, 9, 5, 0, 0, 0},
                                {0, 9, 8, 0, 0, 0, 0, 6, 0},
                                {8, 0, 0, 0, 6, 0, 0, 0, 3},
                                {4, 0, 0, 8, 0, 3, 0, 0, 1},
                                {7, 0, 0, 0, 2, 0, 0, 0, 6},
                                {0, 6, 0, 0, 0, 0, 2, 8, 0},
                                {0, 0, 0, 4, 1, 9, 0, 0, 5},
                                {0, 0, 0, 0, 8, 0, 0, 7, 9}};
    bool result{false};
    clock_t start, finish;
    double total;
    print(grid);
    start = clock();
    result = solve(grid);
    finish = clock();
    total = (double) (finish - start) / CLOCKS_PER_SEC;
    if (result) {
        print(grid);
        cout << "total time: " << total << "s" << endl;
    } else {
        cout << "dead sodoku" << endl << endl;
    }
    return 0;
}