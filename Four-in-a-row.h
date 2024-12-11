#ifndef BOARD_GAMES_FOUR_IN_A_ROW_H
#define BOARD_GAMES_FOUR_IN_A_ROW_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include<limits>
using namespace std;

// Four-in-a-Row Board Class
template <typename T>
class FourInARowBoard : public Board<T> {
public:
    FourInARowBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

// Four-in-a-Row Player Class
template <typename T>
class FourInARowPlayer : public Player<T> {
public:
    FourInARowPlayer(string name, T symbol);
    void getmove(int& x, int& y);
};
// Four-in-a-Row Random Player Class
template <typename T>
class FourInARowRandomPlayer : public RandomPlayer<T> {
public:
    FourInARowRandomPlayer(T symbol);
    void getmove(int& x, int& y);
};

/*----------------------------------- IMPLEMENTATION -----------------------------------*/
template <typename T>
FourInARowBoard<T>::FourInARowBoard() {
    this->rows = 6;
    this->columns = 7;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
template <typename T>
bool FourInARowBoard<T>::update_board(int x, int y, T symbol) {
    if (y < 0 || y >= this->columns || this->board[0][y] != 0) return false; // Invalid move
    // game played from bottom rows not top
    for (int i = this->rows - 1; i >= 0; i--) {
        if (this->board[i][y] == 0) {
            this->board[i][y] = symbol;
            this->n_moves++;
            return true;
        }
    }
    return false;
}
template <typename T>
void FourInARowBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "| ";
        for (int j = 0; j < this->columns; j++) {
            cout << (this->board[i][j] ? this->board[i][j] : ' ') << " | ";
        }
        cout << endl;
    }
    cout << "-----------------------------" << endl;
}
template <typename T>
bool FourInARowBoard<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0) continue;

            // Horizontal
            if (j + 3 < this->columns && this->board[i][j] == this->board[i][j + 1] && this->board[i][j] == this->board[i][j + 2] && this->board[i][j] == this->board[i][j + 3])
                return true;

            // Vertical
            if (i + 3 < this->rows && this->board[i][j] == this->board[i + 1][j] && this->board[i][j] == this->board[i + 2][j] && this->board[i][j] == this->board[i + 3][j])
                return true;

            // Diagonal (/)
            if (i + 3 < this->rows && j + 3 < this->columns && this->board[i][j] == this->board[i + 1][j + 1] && this->board[i][j] == this->board[i + 2][j + 2] && this->board[i][j] == this->board[i + 3][j + 3])
                return true;

            // Diagonal (\)
            if (i + 3 < this->rows && j - 3 >= 0 && this->board[i][j] == this->board[i + 1][j - 1] && this->board[i][j] == this->board[i + 2][j - 2] && this->board[i][j] == this->board[i + 3][j - 3])
                return true;
        }
    }
    return false;
}

// Check for a draw
template <typename T>
bool FourInARowBoard<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}
// Check if the game is over
template <typename T>
bool FourInARowBoard<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
FourInARowPlayer<T>::FourInARowPlayer(string name, T symbol) : Player<T>(name, symbol) {}
template <typename T>
void FourInARowPlayer<T>::getmove(int& x, int& y) {
    cout << "Enter the column (0 to 6): ";
    while (true) {
        cin >> y;
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter an integer value: ";
        } else {
            break;
        }
    }
    x = 0; // Rows will be calculated as the lowest available empty position from the bottom.
}


template <typename T>
FourInARowRandomPlayer<T>::FourInARowRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}
// Generate a random move
template <typename T>
void FourInARowRandomPlayer<T>::getmove(int& x, int& y) {
    y = rand() % this->dimension;
    x = 0;
}

#endif //BOARD_GAMES_FOUR_IN_A_ROW_H
