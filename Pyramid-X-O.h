#ifndef BOARD_GAMES_PYRAMID_X_O_H
#define BOARD_GAMES_PYRAMID_X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

/// Problem 1: Pyramid Tic Tac Toe ///

// CLass of player of xo game
template <class T>
class Human_Player : public Player<T> {
public:
    Human_Player(string n, T s) : Player<T>(n, s) {}

    void getmove(int& x, int& y) override {
        // Asking user to enter the index
        cout << "--> { " << this->getname() << " } Please enter your move's row and column (symbol "
             << this->getsymbol() << "): ";
        cin >> x >> y;

        // Adding boundaries of the row and column
        if (x < 0 || x > 2 || y < 0 || y > 4) {
            cerr << "--> OUT OF BOUNDS!" << endl;
        }

        // Check if the move is valid for the triangular board layout
        if ((x == 0 && y != 2) ||
            (x == 1 && (y < 1 || y > 3)) ||
            (x == 2 && (y < 0 || y > 4))) {
            cerr << "--> OUT OF PYRAMID SHAPE!" << endl;
        }
    }
};

// Class if the random player
template <class T>
class Random_Player1 : public RandomPlayer<T> {
public:
    Random_Player1(T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 3; // 3 rows (valid x values: 0, 1, 2)
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));  // Seed the random generator
    }

    void getmove(int& x, int& y) override {
        // Random row (0 to 2)
        x = rand() % this->dimension;
        // Random column (0 to 4)
        y = rand() % 5;
    }

};


template < class T>
class GameOne : public Board<T>{
    char arr[3][5]{}; // Array to store the input
public:
    GameOne() {
        // Initialize the array cells with space
        for (auto & i : arr){
            for (char & j : i){
                j = ' ';
            }
        }
    }
    void display_board() override {
        cout << "      0   1   2   3   4\n";  // Column headers with alignment
        for (int i = 0; i < 3; ++i) {
            // Adjust row alignment based on the row index to create a triangular shape
            if (i == 0) cout << "   ";
            else if (i == 1) cout << "   ";
            else if (i == 2) cout << "   ";

            // Print the row index on the left
            cout << i << " ";

            // Display the board cells
            for (int j = 0; j < 5; ++j) {
                if ((i == 0 && j == 2) || (i == 1 && j >= 1 && j <= 3) || (i == 2)) {
                    cout << "[" << arr[i][j] << "] ";
                } else {
                    cout << "    ";  // Empty spaces for alignment
                }
            }
            cout << endl;  // Move to the next line after finishing the row
        }
        cout << endl;
    }
    char last_symbol{};
    bool update_board(int x, int y, char symbol) override {
        // Check if the coordinates are within bounds
        if (x < 0 || x > 2 || y < 0 || y > 4) {
            return false;
        }

        // Check if the move is valid for the triangular board layout
        if ((x == 0 && y != 2) ||
            (x == 1 && (y < 1 || y > 3)) ||
            (x == 2 && (y < 0 || y > 4))) {
            return false;
        }

        // Check if the position is already taken
        if (arr[x][y] != ' ') {
            return false;
        }

        // Update the board with the new move
        arr[x][y] = symbol;
        last_symbol = symbol;  // Store the last played symbol
        return true;
    }

    bool is_win() override {
        char symbol = last_symbol;

        // VERTICALLY
        for (int i = 0; i < 3; i++) {
            if (i + 2 < 3 && arr[i][2] == symbol && arr[i + 1][2] == symbol && arr[i + 2][2] == symbol) {
                return true;
            }

        }

        // HORIZONTALLY
        for (int i = 1 ; i < 4; i++){
            if (i + 2 < 4 && arr[1][i] == symbol && arr[1][i+1] == symbol && arr[1][i+2] == symbol){
                return true;
            }
        }
        for (int i = 0 ; i < 5 ; i++){
            if (i + 2 < 3 && arr[2][i] == symbol && arr[2][i+1] == symbol && arr[2][i+2] == symbol){
                return true;
            }
            else if (i + 3 < 4 && arr[2][i+1] == symbol && arr[2][i+2] == symbol && arr[2][i+3] == symbol){
                return true;
            }
            else if (i + 4 < 5 && arr[2][i+2] == symbol && arr[2][i+3] == symbol && arr[2][i+4] == symbol){
                return true;
            }
        }

        // DIAGONALLY
        for (int i = 0; i + 2 < 3; ++i) {
            for (int j = 0; j + 2 < 5; ++j) {
                if (arr[i][j] == symbol && arr[i + 1][j + 1] == symbol && arr[i + 2][j + 2] == symbol) {
                    return true;
                }
            }
        }
        for (int i = 0; i + 2 < 3; ++i) {
            for (int j = 2; j - 2 >= 0; --j) {
                if (arr[i][j] == symbol && arr[i + 1][j - 1] == symbol && arr[i + 2][j - 2] == symbol) {
                    return true;
                }
            }
        }
        return false;
    }
    bool is_draw() override {
        // When all the cells is full so it's draw
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 5; ++j) {
                if ((i == 0 && j == 2) || (i == 1 && j >= 1 && j <= 3) || (i == 2)) {
                    if (arr[i][j] == ' ') return false;
                }
            }
        }
        return true;
    }
    // Game ends when someone wins or all the cells are full
    bool game_is_over() override {
        return is_draw() || is_win();
    }
};

#endif //BOARD_GAMES_PYRAMID_X_O_H
