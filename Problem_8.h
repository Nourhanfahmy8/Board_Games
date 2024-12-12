#ifndef BOARD_GAMES_PROBLEM_8_H
#define BOARD_GAMES_PROBLEM_8_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
using namespace std;

Player<char>* global_Players[2];
static bool israndom_player1 = false;
static bool israndom_player2 = false;

template <typename T>
class TicTacToe {
private:
    vector<vector<T>> small_board; // 3x3 grid for the smaller Tic Tac Toe game
    int nMoves;

public:
    TicTacToe();
    void display_row(int row); // For displaying specific rows
    bool updateB(int x, int y, T symbol); // updating the grid with the input symbol
    bool update_win(int x, int y, T symbol); // to update the small grid with the players symbol
    bool isWinner(T symbol);
    bool isDraw(T symbol);
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
// display row of the grid
void TicTacToe<T>::display_row(int row) {
    cout << "   ";
    for (int j = 0; j < 3; j++) {
        cout << "{" << small_board[row][j] << "}";
        if (j < 2) cout << "";
    }
}

template <typename T>
bool TicTacToe<T>::updateB(int x, int y, T symbol) {

    // validation check if the input is out of bounds
    if (x < 0 || x >= 3 || y < 0 || y >= 3) {
        //cerr << "\nInvalid input! The input is out of bounds, please input an index value between 0 and 2\n" << endl;
        return false;
    }

        // checking if the small board index is not empty
    else if (small_board[x][y] != ' ') {
        //cout << "\nThe cell is already occupied!\n" << endl;
        return false;
    }

    // if the input is valid, the symbol of the current player will be set at that index
    small_board[x][y] = symbol;
    nMoves++;
    return true;
}


// function to set the small grid with the symbol of the winning player
template <typename T>
bool TicTacToe<T>::update_win(int x, int y, T symbol) {
    // setting the index given to the function with the players symbol
    small_board[x][y] = symbol;
    return true;
}

// checking if there is a winner
template <typename T>
bool TicTacToe<T>::isWinner(T symbol) {

    // Checking the rows of each of the small board
    for (int i = 0; i < 3; i++) {
        if (small_board[i][0] == symbol && small_board[i][1] == symbol && small_board[i][2] == symbol) {
            nMoves++;
            return true;
        }
    }

    // Check the columns of each of the small board
    for (int i = 0; i < 3; i++) {
        if (small_board[0][i] == symbol && small_board[1][i] == symbol && small_board[2][i] == symbol) {
            nMoves++;
            return true;
        }
    }

    // Check the diagonals
    if (small_board[0][0] == symbol && small_board[1][1] == symbol && small_board[2][2] == symbol) {
        nMoves++;
        return true;
    }
    if (small_board[0][2] == symbol && small_board[1][1] == symbol && small_board[2][0] == symbol) {
        nMoves++;
        return true;
    }

    // no winner after checking
    return false;
}

template <typename T>
bool TicTacToe<T>::isDraw(T symbol) {
    if(nMoves == 9){
        cout << "Draw for sub-board\n";
        return true;
    }
    return false;
}
// initializing the main big board with empty space
template <typename T>
Ultimate_Tic_Tac_Toe<T>::Ultimate_Tic_Tac_Toe()
        : board(3, vector<TicTacToe<T>>(3)), main_board(3, vector<T>(3, ' ')) {}


// update board
template <typename T>
bool Ultimate_Tic_Tac_Toe<T>::update_board(int big_x, int big_y, T symbol) {

    // Check if it's Player 1's turn
    if (this->n_moves % 2 == 0) {
        // Player 1
        if (!israndom_player1) {
            // player 1 is a human
            cout << "\nPlayer '1' : Please enter the large grid indices (0-2) of the grid you want to play in\n";
            while(true) {

                cin >> big_x >> big_y;
                // validation check on the input
                if (cin.fail() || big_x < 0 || big_x >= 3 || big_y < 0 || big_y >= 3) {
                    cerr << "\nInvalid input! Please input a valid index value from 0 to 2\n" << endl;
                    cin.clear();          // Clear the input stream
                    cin.ignore(1000, '\n'); // Ignore remaining input
                    //return false;
                    continue;
                }
                // check if the input main board cell is not empty
                if (main_board[big_x][big_y] != ' ') {
                    cerr << "\nMain board cell is already occupied, Please choose a different main board cell\n" << endl;
                    //return false;
                    continue;
                } else break;
            }

            TicTacToe<T>& sub_board = board[big_x][big_y];
            int small_x, small_y;
            cout << "\nPlayer '1' "
                 << "-> Please enter the small grid cell indices you want to place your token in, within the selected sub-board\n";
            while(true) {
                cin >> small_x >> small_y;

                if (cin.fail() || small_x < 0 || small_x >= 3 || small_y < 0 || small_y >= 3) {
                    cerr << "\nInvalid input! Please input a valid index value from 0 to 2\n" << endl;
                    cin.clear();          // Clear the input stream
                    cin.ignore(1000, '\n'); // Ignore remaining input
                    //return false;
                    continue;
                }

                if (!sub_board.updateB(small_x, small_y, symbol)) {
                    cerr << "\nInvalid move within the sub-board. Try again.\n";
                    continue;
                }
                else break;

            }
        } else {
            // Player 1 is random
            do {
                big_x = rand() % 3;
                big_y = rand() % 3;
            } while (main_board[big_x][big_y] != ' '); // Ensure the chosen sub-board is not already claimed

            TicTacToe<T>& sub_board = board[big_x][big_y];
            int small_x, small_y;

            do {
                small_x = rand() % 3;
                small_y = rand() % 3;
            } while (!sub_board.updateB(small_x, small_y, symbol)); // Ensure the cell is valid and unoccupied
        }
    } else {
        // Player 2
        if (!israndom_player2) {
            // Player 2 is a human
            cout << "\nPlayer '2' "
                 << "-> Please enter the large grid indices (0-2) of the grid you want to play in\n";
            while (true) {
                cin >> big_x >> big_y;
                // validation check on the input
                if (cin.fail() || big_x < 0 || big_x >= 3 || big_y < 0 || big_y >= 3) {
                    cerr << "\nInvalid input! Please input a valid index value from 0 to 2\n" << endl;
                    cin.clear();          // Clear the input stream
                    cin.ignore(1000, '\n'); // Ignore remaining input
                    continue;
                    //return false;
                }

                if (main_board[big_x][big_y] != ' ') {
                    cerr << "\nMain board cell already occupied!\n" << endl;
                    continue;
                    //return false;
                } else break;
            }
            TicTacToe<T> &sub_board = board[big_x][big_y];
            int small_x, small_y;

            cout << "\nPlayer '2' "
                 << "-> Please enter the small grid cell indices you want to place your token in, within the selected sub-board\n";
            while (true) {
                cin >> small_x >> small_y;
                if (cin.fail() || small_x < 0 || small_x >= 3 || small_y < 0 || small_y >= 3) {
                    cerr << "\nInvalid input! Please input a valid index value from 0 to 2\n" << endl;
                    cin.clear();          // Clear the input stream
                    cin.ignore(1000, '\n'); // Ignore remaining input
                    //return false;
                    continue;
                }
                if (!sub_board.updateB(small_x, small_y, symbol)) {
                    cerr << "\nInvalid move within the sub-board. Try again.\n";
                    continue;
                    //return false;
                } else break;
            }

        } else {
            // Player 2 is random
            do {
                big_x = rand() % 3;
                big_y = rand() % 3;
            } while (main_board[big_x][big_y] != ' '); // Ensure the chosen sub-board is not already claimed

            TicTacToe<T> &sub_board = board[big_x][big_y];
            int small_x, small_y;

            do {
                small_x = rand() % 3;
                small_y = rand() % 3;
            } while (!sub_board.updateB(small_x, small_y, symbol)); // Ensure the cell is valid and unoccupied
        }
    }

    /// Check if the input move by the player makes the player win in the small board
    TicTacToe<T> &sub_board = board[big_x][big_y];
    if (sub_board.isWinner(symbol)) {
        // if player 1 got the 3 in a row in one of the small grids
        if (symbol == 'X') {
            cout << "\n** Player 1 has won in this sub-board **\n";
            // setting the small grid with the symbol 'X'
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (i == 0 && j == 0 || i == 0 && j == 2 || i == 1 && j == 1 || i == 2 && j == 0 ||
                        i == 2 && j == 2) {
                        sub_board.update_win(i, j, 'x'); // Fill the sub-board with the winner's symbol
                    } else sub_board.update_win(i, j, ' ');
                }
            }
            // player 2 got 3 in a row in one of the small grids
        } else if (symbol == 'O') {
            cout << "\n** Player 2 has won in this sub-board **\n";
            // filling the small sub board with player 2's symbol 'O'
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (i == 1 && j == 1) {
                        sub_board.update_win(i, j, ' ');
                    } else sub_board.update_win(i, j, 'O');// Fill the sub-board with the winner's symbol
                }
            }
        }
        main_board[big_x][big_y] = symbol; // Mark the main board
    }
    if(sub_board.isDraw(symbol)){
        cerr << "\nDraw of this sub-board!\n";
    }
    this->n_moves++; // Increment the move counter
    return true;
}

// display the board
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
        cout << "\nIt's a draw!\n" << endl;
        return true;
    }
    return false;
}

// game is over if there is a winner of the game is a draw
template<typename T>
bool Ultimate_Tic_Tac_Toe<T>::game_is_over() {
    return is_win() || is_draw();
}

template<typename T>
Ultimate_Player<T>::Ultimate_Player(std::string name, T symbol) :  Player<T>(name, symbol) {}

// Get move from a human player
template <typename T>
void Ultimate_Player<T>::getmove(int& big_x, int& big_y) {

    // the get move from the player is implemented in the update board

}

template <typename T>
Random_Ultimate_Player<T>::Random_Ultimate_Player(T symbol) : RandomPlayer<T>(symbol){
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

// get random move from the random computer player
template <typename T>
void Random_Ultimate_Player<T>::getmove(int &x, int &y) {
    // Random row index
    x = rand() % this->dimension;
    // Random column index
    y = rand() % this->dimension;
}


#endif //BOARD_GAMES_PROBLEM_8_H