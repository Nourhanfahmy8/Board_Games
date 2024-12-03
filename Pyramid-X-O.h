#ifndef BOARD_GAMES_PYRAMID_X_O_H
#define BOARD_GAMES_PYRAMID_X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

template <class T>
class Human_Player : public Player<T> {
public:
    Human_Player(string n, T s) : Player<T>(n, s) {}

    void getmove(int& x, int& y) override {
        cout << "{ " << this->getname() << " } Please enter your move's row and column (symbol "
             << this->getsymbol() << "): ";
        cin >> x >> y;
    }
};

template <class T>
class Random_Player1 : public RandomPlayer<T> {
public:
    Random_Player1(T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 3;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));  // Seed the random generator
    }

    void getmove(int& x, int& y) override {
        do {
            x = rand() % 3;  // Random row (0 to 2)
            y = rand() % 5;  // Random column (0 to 4)
        } while (!this->boardPtr->update_board(x, y, this->getsymbol())); // Ensure move is valid
    }
};


template < class T>
class GameOne : public Board<T>{
    char arr[3][5]{};
public:
    GameOne() {
        for (int i = 0 ; i < 3 ; i++){
            for (int j = 0 ; j < 5 ; j++){
                arr[i][j] = ' ';
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
    }
    char last_symbol;
    bool update_board(int x, int y, char symbol) override {
        if (x > 2 || x < 0 || y > 4 || y < 0) {
            cerr << "OUT OF BOUNDS! Please enter again." << endl;
            return false;
        }
        if (arr[x][y] != ' ') {
            cerr << "POSITION ALREADY TAKEN! Please choose another." << endl;
            return false;
        }
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
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 5; ++j) {
                if ((i == 0 && j == 2) || (i == 1 && j >= 1 && j <= 3) || (i == 2)) {
                    if (arr[i][j] == ' ') return false;
                }
            }
        }
        return true;
    }
    bool game_is_over() override {
        return is_draw() || is_win();
    }
};

#endif //BOARD_GAMES_PYRAMID_X_O_H
