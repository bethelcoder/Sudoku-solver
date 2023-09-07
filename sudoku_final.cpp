#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
class sudoku_functions{
public:
    int ret_row = 0;
    int ret_col = 0;
    static bool isComplete(vector<vector<int>>&sudoku);
    bool isValidDigit(vector<vector<int>>&sudoku, int row, int col, int digit);
    void emptyCell(vector<vector<int>>&sudoku);
};
bool sudoku_functions::isComplete(vector<vector<int>> &sudoku) {
    int indicator = 0;
    for (auto & r : sudoku) {
        for (int c : r) {
            if(c == indicator){
                return false;
            }
        }
    }
    return true;
}
bool sudoku_functions::isValidDigit(vector<vector<int>> &sudoku, int row, int col, int digit) {
    // Assuming n is the size of the Sudoku grid (e.g., 9)

    // Check if the digit is valid in the same row
    for (int c = 0; c < 9; c++) {
        if (sudoku[row][c] == digit && c != col) {
            return false; // Duplicate digit in the same row
        }
    }

    // Check if the digit is valid in the same column
    for (int r = 0; r < 9; r++) {
        if (sudoku[r][col] == digit && r != row) {
            return false; // Duplicate digit in the same column
        }
    }

    // Determine the dimensions of the 3x3 subgrid
    int boxSize = sqrt(9); // Assuming each grid box is sqrt(n) x sqrt(n)

    // Calculate the starting row and column of the subgrid
    int boxStartRow = (row / boxSize) * boxSize;
    int boxStartCol = (col / boxSize) * boxSize;

    // Check if the digit is valid in the same 3x3 subgrid
    for (int r = boxStartRow; r < boxStartRow + boxSize; r++) {
        for (int c = boxStartCol; c < boxStartCol + boxSize; c++) {
            if (sudoku[r][c] == digit && (r != row || c != col)) {
                return false; // Duplicate digit in the same subgrid
            }
        }
    }

    return true; // Digit
}
void sudoku_functions::emptyCell(vector<vector<int>> &sudoku) {
    int indicator = 0;
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (sudoku[r][c] == indicator) {
                ret_row = r;
                ret_col = c;
                return; // Found the first empty cell, return immediately
            }
        }
    }
}
bool solve(vector<vector<int>> &sudoku){
    sudoku_functions collectives;
    if(collectives.isComplete(sudoku)){
        return true;
    }
    collectives.emptyCell(sudoku);
    int row = collectives.ret_row;
    int col = collectives.ret_col;
    for(int digit = 1; digit <= 9; digit++){
        if(collectives.isValidDigit(sudoku, row, col, digit)){
            sudoku[row][col] = digit;
            if(solve(sudoku)){
                return true;
            }
            sudoku[row][col] = 0;
        }
    }
    return false;
}
int main(){
    const int n = 9;
    vector<vector<int>> sudoku(n, vector<int>(n));
    for(int r = 0; r < 9; r++){
        for(int c = 0; c < 9; c++){
            cin >> sudoku[r][c];
        }
    }
if(solve(sudoku)){
    for(int r = 0; r < 9; r++){
        for(int c = 0; c < 9; c++){
            cout << sudoku[r][c] << " ";
        }
        cout << endl;
    }
} else {
    cout << "No solution" << endl;
}
    return 0;
}
