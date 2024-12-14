#ifndef BOARD_GAMES_TICTACTOE_H
#define BOARD_GAMES_TICTACTOE_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>

/// ----- PROBLEM 3 : 5*5 Tic Tac Toe ----- ///


Player<char>* global_Players[2];
static bool israndom_player1 = false;
static bool israndom_player2 = false;


/// Class of 5*5 Tic Tac Toe
template <typename T>
class TicTacToeBoard: public Board<T>{
public:
    TicTacToeBoard();
    bool update_board(int x,int y,T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    int counter_three_in_a_row(T symbol);
};


/// Class of 5*5 Tic Tac Toe player
template <typename T>
class TicTacToePlayer : public Player <T>{
public:
    TicTacToePlayer(string name, T symbol);
    void getmove(int &x, int&y);
};

/*---------- IMPLEMENTATION ----------*/

/// constructor for 5*5 tic Tac Toe player
template <typename T>
TicTacToePlayer<T>::TicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}


/// Get move from a human player
template <typename T>
void TicTacToePlayer<T>::getmove(int& x, int& y) {
    // asking the human player to input the cell index they want
    cout << "\n-> Player '" << this-> getname() << "' : Please input the cell index you want separated with a space\n";
}

/// Random player class and implementation
template <class T>
class Random_Player : public RandomPlayer<T> {
public:
    Random_Player(T symbol) : RandomPlayer<T>(symbol) {
        // setting the default dimension and name for random player
        this->dimension = 5;
        this -> name = "Random Computer Player";
        // Seed the random generator
        srand(static_cast<unsigned int>(time(0)));
    }
    // function to get the random cell index for the random player
    void getmove(int& x, int& y) override {
        // Random row (0 to 4)
        x = rand() % this->dimension;
        // Random column (0 to 4)
        y = rand() % 5;
    }

};


template <typename T>
/// initialize the board with empty spaces
TicTacToeBoard <T>::TicTacToeBoard(){
    this -> rows = 5;
    this-> columns = 5;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            // each cell is initialized to an empty cell
            this->board[i][j] = ' ';
        }
    }
    // initialize the number of moves to be equal 0
    this->n_moves = 0;
}


template <typename T>
/// updating the board with each input move by the computer player or the user after validating it
bool TicTacToeBoard<T> :: update_board(int x, int y, T symbol) {

    // Check if it's Player 1's turn
    if (this->n_moves % 2 == 0) {
        // Player 1
        if (!israndom_player1) {
            // Player 1 is a human

                // if the user inputs a row index less than 0 or greater than 4 --> out of bounds
                // or if the user inputs a column index less than 0 or greater than 4 --> out of bounds
                while (true) {
                    cin >> x >> y;
                    // validation check on the input
                    if (cin.fail() || x < 0 || x >= 5 || y < 0 || y >= 5) {
                        cerr << "\nInvalid input! Please input a valid cell index between 0 and 4 inclusive\n" << endl;
                        cin.clear();          // Clear the input stream
                        cin.ignore(1000, '\n'); // Ignore remaining input
                        continue;
                    } else if (this->board[x][y] != ' ') {
                        // The user chooses a cell which isn't empty meaning it has been chosen before --> move can't be made
                        cerr << "\nThis cell has already been chosen, Please choose another cell\n";
                    } else break;
                }
        } else {
            // Player 1 is random
            do {
                // Random row (0 to 4)
                x = rand() % 5;
                // Random column (0 to 4)
                y = rand() % 5;
            } while (this->board[x][y] != ' ');
        }
    } else {
        // Player 2
        if (!israndom_player2) {
            // player 2 is a human

                // if the user inputs a row index less than 0 or greater than 4 --> out of bounds
                // or if the user inputs a column index less than 0 or greater than 4 --> out of bounds
                while (true) {
                    cin >> x >> y;
                    // validation check on the input
                    if (cin.fail() || x < 0 || x >= 5 || y < 0 || y >= 5) {
                        cerr << "\nInvalid input! Please input a valid cell index between 0 and 4 inclusive\n" << endl;
                        cin.clear();          // Clear the input stream
                        cin.ignore(1000, '\n'); // Ignore remaining input
                        continue;
                    } else if (this->board[x][y] != ' ') {
                        // The user chooses a cell which isn't empty meaning it has been chosen before --> move can't be made
                        cerr << "\nThis cell has already been chosen, Please choose another cell\n";
                    } else break;
                }
        } else {
            // player 2 is random
            do {
                // Random row (0 to 4)
                x = rand() % 5;
                // Random column (0 to 4)
                y = rand() % 5;
            } while (this->board[x][y] != ' ');
        }
    }

    // the cell will be updated with the symbol if input is valid --> either X or O according to each player
    this->board[x][y] = toupper(symbol);
    // the number of moves will be incremented until it reaches 24 when the game ends
    this->n_moves++;
    return true;
}


/// displaying the board after each turn
template <typename T>
void TicTacToeBoard<T> :: display_board() {

    // outputting a message for the user after each turn to tell him the number of turns played
    cout << "\n --- The board at move " << this->n_moves << " ---\n";
    // output the column index numbers at the top for better visibility for the user when choosing input
    cout << "    ";
    for(int x=0;x<5;x++){
        cout  << x << "   ";
    }
    cout << endl;

    // output the grid
    for (int i = 0; i < 5; i++) {
        // output the row index number for better visibility for the user
        cout << i << " | ";
        for (int j = 0; j < 5; j++) {

            // outputting the contents of each cell
            cout << this->board[i][j];
            // putting a separator between each column cell
            if (j < 4) cout << " | ";
        }
        cout << " |";
        cout << "\n";
        // putting a separator between each row
        if (i < 4) cout << "  ---------------------\n";
    }
    cout << "  ---------------------\n";
    cout << endl;
}


/// Check if the game is draw -> return true if 24 moves have been done and no winner
template <typename T>
bool TicTacToeBoard<T>::is_draw() {
    return  (this->n_moves == 24 && !is_win());
}


/// check if the game is over meaning that 24 moves have been done
template <typename T>
bool TicTacToeBoard<T>::game_is_over() {
    // either there is a winner or both players are draw
    return is_win() || is_draw();
}


/// counting three-in-a-rows for each player
/// will count for each player the three-in-a-rows in columns vertically, rows horizontally, and diagonally
template <typename T>
int TicTacToeBoard<T>::counter_three_in_a_row(T symbol) {
    int counter = 0;

    // checking horizontally for three in a row in rows
    for (int i = 0; i < 5; i++) {
        // counting for 3 cells only each time, so will only check for 3 columns everytime
        for (int j = 0; j < 3; j++) {

            // if the 3 cells next to each other are the same symbol, the counter will be incremented
            if ( (this->board[i][j] == symbol) && (this->board[i][j + 1] == symbol) && (this->board[i][j + 2] == symbol)) {
                counter++;
            }
        }
    }

    // Check vertically for three in a row in columns
    for (int j = 0; j < 5; j++) {
        // will only check for 3 cells each time, so will only check for 3 row cells each time
        for (int i = 0; i < 3; i++) {

            // if the 3 cells below each other are the same symbol, the counter will be incremented
            if ( (this->board[i][j] == symbol) && (this->board[i + 1][j] == symbol) && (this->board[i + 2][j] == symbol)) {
                counter++;
            }
        }
    }


    // Checking diagonals for each cell from left and right
    // only check 3 cells, so for 3 rows and 3 columns each time
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            if ( (this->board[i][j] == symbol) && (this->board[i + 1][j + 1] == symbol) && (this->board[i + 2][j + 2] == symbol)) {
                counter++;
            }
        }
    }

    // Check diagonals (right to left)
    for (int i = 0; i < 3; i++) {
        for (int j = 2; j < 5; j++) {

            // checking the diagonal cells
            if ( (this->board[i][j] == symbol && this->board[i + 1][j - 1]) == symbol && (this->board[i + 2][j - 2] == symbol)) {
                counter++;
            }
        }
    }
    return counter;
}

/// checking if there is a winner after the 24 moves have been done
template <typename T>
bool TicTacToeBoard<T>:: is_win(){
    // getting the number of 3 in a rows for first player
    int first_player = counter_three_in_a_row('X');
    // getting the number of 3 in a rows for second payer
    int second_player = counter_three_in_a_row('O');

    // check if the number of moves is 24, meaning that the game ended and can see if there is a winner
    if(this->n_moves == (24)){
        // player 1 wins
        if(first_player > second_player ){
            // setting the global winner player's pointer value to first player's name
            *global_Players[1] = *global_Players[0];
            return true;
        }
        // player 2 wins
        if(first_player < second_player){
            return true;
        }
    }
    return false;
}

#endif //BOARD_GAMES_TICTACTOE_H