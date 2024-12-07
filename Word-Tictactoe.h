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

    void getmove(int& x, int& y) override {
        char character;
        cout << "--> { " << this->getname() << " } Enter your move's row, column, and character (A-Z):";
        cin >> x >> y >> character;

        // Validate coordinates and character input
        while (x < 0 || x >= 3 || y < 0 || y >= 3 || character < 'A' || character > 'Z') {
            cerr << "--> Invalid input! Enter row (0-2), column (0-2), and a uppercase letter (A-Z):";
            cin >> x >> y >> character;
        }
        // Convert character to uppercase in HumanPlayer
        character = toupper(character);
        this->symbol = character;
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
        cout << "------------------------------\n";
        x = rand() % 3;
        y = rand() % 3;
        char character = 'A' + rand() % 26;  // Generate a random lowercase letter
        this->symbol = character;  // Store the character in the player's symbol field
    }
};

template <class T>
class GameFour : public Board<T>{
    char arr2[3][3]{};
    set <string> dictionary;
public:
    GameFour() {
        for (auto &i : arr2) {
            for (char &j : i) {
                j = ' ';
            }
        }
        loadFromFile("dic.txt");
    }

    // Load dictionary from file
    void loadFromFile(const string& filename) {
        ifstream infile(filename);
        if (!infile) {
            cerr << "--> Dictionary file not found!\n";
            return;
        }
        string word;
        // Convert dictionary words to uppercase when loading
        while (infile >> word) {
            for (char &c : word) c = toupper(c);
            dictionary.insert(word);
        }

    }

    // Display the board
    void display_board() override {
        cout << "     0   1   2\n";
        for (int i = 0; i < 3; ++i) {
            cout << "  " << i << " ";
            for (int j = 0; j < 3; ++j) {
                cout << "[" << arr2[i][j] << "] ";
            }
            cout << endl;
        }
    }

    // Update board with the player's move
    bool update_board(int x, int y, T symbol) override {
        // Ensure that the coordinates are within the bounds of the 3x3 board
        if (x < 0 || x >= 3 || y < 0 || y >= 3) {
            cerr << "--> OUT OF BOUNDS! Please enter again." << endl;
            return false;
        }
        if (arr2[x][y] != ' ') {
            cerr << "--> POSITION ALREADY TAKEN! Please choose another." << endl;
            return false;
        }

        // Place the character on the board
        arr2[x][y] = symbol;
        this->n_moves++;
        return true;
    }


    // Check for valid words in file
    bool is_valid_word() {
        // Check rows
        for (int i = 0; i < 3; ++i) {
            string row;
            for (int j = 0; j < 3; ++j) {
                row += arr2[i][j];
            }
            // Means row's word is found in the dictionary file
            if (dictionary.find(row) != dictionary.end()) {
                return true;
            }
        }

        // Check columns
        for (int j = 0; j < 3; ++j) {
            string col;
            for (int i = 0; i < 3; ++i) {
                col += arr2[i][j];
            }
            // Means column's word is found in the dictionary file
            if (dictionary.find(col) != dictionary.end()) {
                return true;
            }
        }

        // Check diagonals
        string diag1, diag2;
        for (int i = 0; i < 3; ++i) {
            diag1 += arr2[i][i];
            diag2 += arr2[i][2 - i];
        }
        // Means diagonal1's word and diagonal2's are found in the dictionary file
        if (dictionary.find(diag1) != dictionary.end() || dictionary.find(diag2) != dictionary.end()) {
            return true;
        }

        // The words are not found
        return false;
    }
    string get_winning_word() {
        // Check rows for a winning word
        for (int i = 0; i < 3; ++i) {
            string row;
            for (int j = 0; j < 3; ++j) {
                row += arr2[i][j];
            }
            if (dictionary.find(row) != dictionary.end()) {
                return row; // Return the winning word from the row
            }
        }

        // Check columns for a winning word
        for (int j = 0; j < 3; ++j) {
            string col;
            for (int i = 0; i < 3; ++i) {
                col += arr2[i][j];
            }
            if (dictionary.find(col) != dictionary.end()) {
                return col; // Return the winning word from the column
            }
        }

        // Check diagonals for a winning word
        string diag1, diag2;
        for (int i = 0; i < 3; ++i) {
            diag1 += arr2[i][i];
            diag2 += arr2[i][2 - i];
        }
        if (dictionary.find(diag1) != dictionary.end()) {
            return diag1; // Return the winning word from the first diagonal
        }
        if (dictionary.find(diag2) != dictionary.end()) {
            return diag2; // Return the winning word from the second diagonal
        }

        return ""; // No winning word found
    }


    // Check if the game is won
    bool is_win() override {
        string winning_word = get_winning_word();
        if (!winning_word.empty()) {
            cout << "Congratulations! The winning word is: " << winning_word << endl;
            return true;
        }
        return false;
    }


    // Check if the game is a draw
    bool is_draw() override {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (arr2[i][j] == ' ') {
                    // To be a draw , must all the cells completed
                    return false;
                }
            }
        }
        // when the game is not win and all cells are completed ,so it's a draw
        return !is_win();
    }

    // Check if the game is over
    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

#endif //BOARD_GAMES_WORD_TICTACTOE_H
