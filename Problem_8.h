#ifndef BOARD_GAMES_PROBLEM_8_H
#define BOARD_GAMES_PROBLEM_8_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class TicTacToe {
private:
    vector<vector<T>> small_board;  // 3x3 grid for the smaller Tic Tac Toe game

public:
    TicTacToe();
    void display_row(int row); // For displaying specific rows
    bool updateB(int x, int y, T symbol);
    bool isWinner(T symbol);
};


template <typename T>
class Ultimate_Tic_Tac_Toe: public Board<T>{
    vector<vector<TicTacToe<T>>> board;   // 3x3 grid of smaller boards
    vector<vector<T>> main_board;
public:
    Ultimate_Tic_Tac_Toe();
    bool update_board(int x,int y,T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Ultimate_Player : public Player <T>{
public:
    Ultimate_Player(string name, T symbol);
    void getmove(int &x, int&y);
};

template <typename T>
class Random_Ultimate_Player : public RandomPlayer <T>{
public:
    Random_Ultimate_Player(T symbol);
    void getmove(int& x,int& y);
};

/*----------------------- IMPLEMENTATION -----------------------*/

template < typename T>
TicTacToe<T>::TicTacToe() : small_board(3, vector<T>(3, ' ')) {}

template <typename T>
void TicTacToe<T>::display_row(int row) {
    cout << "   ";
    for (int j = 0; j < 3; j++) {
        cout << "{" << small_board[row][j] << "}";
        if (j < 2) cout << "";
    }
}

template <typename T>
bool TicTacToe<T>::updateB(int x, int y, T symbol) {
    if (x < 0 || x >= 3 || y < 0 || y >= 3) {
        cout << "Invalid position!" << endl;
        return false;
    }

    if (small_board[x][y] != ' ') {
        cout << "Cell is already occupied!" << endl;
        return false;
    }

    small_board[x][y] = symbol;
    return true;
}

template <typename T>
bool TicTacToe<T>::isWinner(T symbol) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (small_board[i][0] == symbol && small_board[i][1] == symbol && small_board[i][2] == symbol) {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (small_board[0][i] == symbol && small_board[1][i] == symbol && small_board[2][i] == symbol) {
            return true;
        }
    }

    // Check diagonals
    if (small_board[0][0] == symbol && small_board[1][1] == symbol && small_board[2][2] == symbol) {
        return true;
    }
    if (small_board[0][2] == symbol && small_board[1][1] == symbol && small_board[2][0] == symbol) {
        return true;
    }

    return false;
}
template <typename T>
Ultimate_Tic_Tac_Toe<T>::Ultimate_Tic_Tac_Toe()
        : board(3, vector<TicTacToe<T>>(3)), main_board(3, vector<T>(3, ' ')) {}


template <typename T>
bool Ultimate_Tic_Tac_Toe<T>::update_board(int big_x, int big_y, T symbol) {
    if (big_x < 0 || big_x >= 3 || big_y < 0 || big_y >= 3) {
        cerr << "Invalid main board position!" << endl;
        return false;
    }


    // Check if the main board cell is already occupied
    if (main_board[big_x][big_y] != ' ') {
        cerr << "Main board cell already occupied!" << endl;
        return false;
    }
// Get the corresponding sub-board
    TicTacToe<T>& sub_board = board[big_x][big_y];

    // Update the smaller board
    cout << "Enter the cell indices (0-2) within the selected sub-board:\n";
    int small_x, small_y;
    cin >> small_x >> small_y;

    if (!sub_board.updateB(small_x, small_y, symbol)) {
        // Handle invalid moves in the small board
        cerr << "Invalid move within the sub-board. Try again.\n";
        return false;
    }

    // Check if this move wins the small board
    if (sub_board.isWinner(symbol)) {
        cout << "Player " << symbol << " has won this sub-board!\n";
        main_board[big_x][big_y] = symbol; // Mark the main board
    }

    this->n_moves++; // Track total moves

    return true;
}


template <typename T>
void Ultimate_Tic_Tac_Toe<T>::display_board() {
    cout << "\n------ Ultimate Tic Tac Toe Board ------\n\n";

    cout << "        0                 1                 2\n";


    for (int big_row = 0; big_row < 3; big_row++) {  // Iterate over rows of sub-boards
        for (int small_row = 0; small_row < 3; small_row++) {  // Iterate through each row in a sub-board

            for (int big_col = 0; big_col < 3; big_col++) {    // Iterate over sub-boards in the current row
                if(small_row == 1 && big_col == 0){
                    cout << big_row;
                }
                else cout << " ";
                // Display the current row of a sub-board
                board[big_row][big_col].display_row(small_row);
                if (big_col < 2) cout << "   | ";  // Separator between sub-boards
            }
            cout << endl;
        }
        if (big_row < 2) {
            cout << string(50, '=') << endl;  // Separator between sub-board rows
        }
    }
    cout << endl;
}



template< typename T >
bool Ultimate_Tic_Tac_Toe<T>::is_win() {
    // Check if the main board has a winner or if the game is a draw
    for (int i = 0; i < 3; i++) {
        if (this->main_board[i][0] == this->main_board[i][1] && this->main_board[i][1] == this->main_board[i][2] && this->main_board[i][0] != ' ') {
            return true;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (this->main_board[0][i] == this->main_board[1][i] && this->main_board[1][i] == this->main_board[2][i] && this->main_board[0][i] != ' ') {
            return true;
        }
    }
    if (this->main_board[0][0] == this->main_board[1][1] && this->main_board[1][1] == this->main_board[2][2] && this->main_board[0][0] != ' ') {
        return true;
    }
    if (this->main_board[0][2] == this->main_board[1][1] && this->main_board[1][1] == this->main_board[2][0] && this->main_board[0][2] != ' ') {
        return true;
    }
    return false;
}
template <typename T>
bool Ultimate_Tic_Tac_Toe<T>::is_draw() {
    if (this->n_moves == 81) {  // 81 moves in total (9 small boards * 9 cells each)
        cout << "It's a draw!" << endl;
        return true;
    }
    return false;
}
template<typename T>
bool Ultimate_Tic_Tac_Toe<T>::game_is_over() {
    return is_win() || is_draw();
}

template<typename T>
Ultimate_Player<T>::Ultimate_Player(std::string name, T symbol) :  Player<T>(name, symbol) {}

// Get move from a human player
template <typename T>
void Ultimate_Player<T>::getmove(int& big_x, int& big_y) {
    while (true) {
        cout << this->name << "'s turn (Symbol: " << this->symbol << ").\n";
        cout << "Enter the large grid indices (0-2) for your move:\n";

        cin >> big_x >> big_y;

        // Validate input for main board indices
        if (cin.fail() || big_x < 0 || big_x >= 3 || big_y < 0 || big_y >= 3) {
            cout << "Invalid input! Please enter integers between 0 and 2.\n";
            cin.clear();          // Clear the input stream
            cin.ignore(1000, '\n'); // Ignore remaining input
            continue;
        }

        break; // Valid input
    }
}

template <typename T>
Random_Ultimate_Player<T>::Random_Ultimate_Player(T symbol) : RandomPlayer<T>(symbol){
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Random_Ultimate_Player<T>::getmove(int &x, int &y) {
    cout << "------------------------------\n";
    x = rand() % 3;
    y = rand() % 3;
}


#endif //BOARD_GAMES_PROBLEM_8_H
