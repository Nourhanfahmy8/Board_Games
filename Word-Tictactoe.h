#ifndef BOARD_GAMES_WORD_TICTACTOE_H
#define BOARD_GAMES_WORD_TICTACTOE_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <fstream>
#include <set>

using namespace std;
template <class T>
class HumanPlayer : public Player<T> {
public:
    HumanPlayer(string n, T s) : Player<T>(n, s) {}

    void move(int& x, int& y) override {
        cout << "{ " << this->getName() << " } Please enter your move's row and column (symbol "
             << this->getSymbol() << "): ";
        cin >> x >> y;
    }
};

template <class T>
class Random_Player4 : public RandomPlayer<T> {
public:
    Random_Player4(T symbol) : RandomPlayer<T>(symbol) {
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

template <class T>
class GameFour : public Board<T>{
    char arr2[3][3]{};
    set <string> dictionary;
    T lastSymbol;
public:
    GameFour() {
        for (auto &i : arr2) {
            for (char &j : i) {
                j = ' ';
            }
        }
        loadFromFile("dic.txt");  // Load the dictionary file
    }

    // Load dictionary from file
    void loadFromFile(const string& filename) {
        ifstream infile(filename);
        if (!infile) {
            cerr << "Dictionary file not found!\n";
            return;
        }
        string word;
        while (infile >> word) {
            dictionary.insert(word); // Add valid words to the set
        }
    }

    // Display the board
    void display_board() override {
        cout << "      0   1   2\n";
        for (int i = 0; i < 3; ++i) {
            cout << "  " << i << " ";
            for (int j = 0; j < 3; ++j) {
                cout << "[" << arr2[i][j] << "]";
            }
            cout << endl;
        }
    }

    // Update board with the player's move
    bool update_board(int x, int y, T symbol) override {
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || arr2[x][y] != ' ') {
            cerr << "Invalid move! Please try again.\n";
            return false;
        }
        arr2[x][y] = symbol;
        lastSymbol = symbol;
        return true;
    }

    // Check for valid words
    bool is_valid_word(int x, int y) {
        string word;

        // Check horizontal
        word = "";
        for (int j = 0; j < 3; ++j) word += arr2[x][j];
        if (dictionary.find(word) != dictionary.end()) return true;

        // Check vertical
        word = "";
        for (int i = 0; i < 3; ++i) word += arr2[i][y];
        if (dictionary.find(word) != dictionary.end()) return true;

        // Check diagonal (top-left to bottom-right)
        if (x == y) {
            word = "";
            for (int i = 0; i < 3; ++i) word += arr2[i][i];
            if (dictionary.find(word) != dictionary.end()) return true;
        }

        // Check diagonal (top-right to bottom-left)
        if (x + y == 2) {
            word = "";
            for (int i = 0; i < 3; ++i) word += arr2[i][2 - i];
            if (dictionary.find(word) != dictionary.end()) return true;
        }

        return false;
    }

    // Check if the game is won
    bool is_win() override {
        // Scan the board for valid words
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (arr2[i][j] != ' ' && is_valid_word(i, j)) {
                    return true; // Valid word found
                }
            }
        }
        return false;
    }

    // Check if the game is a draw
    bool is_draw() override {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (arr2[i][j] == ' ') return false; // Empty cell found
            }
        }
        return !is_win(); // Draw only if no valid word is formed
    }

    // Check if the game is over
    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

#endif //BOARD_GAMES_WORD_TICTACTOE_H
