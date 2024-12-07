#ifndef BOARD_GAMES_TICTACTOE_H
#define BOARD_GAMES_TICTACTOE_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>

Player<char>* global_Players[2];

// class of Tic Tac Toe
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


// Tic Tac Toe player class
template <typename T>
class TicTacToePlayer : public Player <T>{
public:
    TicTacToePlayer(string name, T symbol);
    void getmove(int &x, int&y);
};


// Tic Tac Toe random player
template <typename T>
class Randomplayer : public RandomPlayer <T>{
public:
    Randomplayer(T symbol);
    void getmove(int& x,int& y);
};




/*----------------------- IMPLEMENTATION -----------------------*/
template <typename T>
// initialize the board with empty spaces
TicTacToeBoard <T>::TicTacToeBoard(){
    this -> rows = 5;
    this-> columns = 5;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    // initialize the number of moves to be equal 0
    this->n_moves = 0;
}


template <typename T>
// updating the board with each input move by the computer player or the user
bool TicTacToeBoard<T> :: update_board(int x, int y, T symbol){

        // if the user inputs a row index less than 0 or greater than 4 --> out of bounds
        // or if the user inputs a column index less than 0 or greater than 4 --> out of bounds
        if (x < 0 || x >= 5 || y < 0 || y >= 5) {
            return false;
        }
        // The user chooses a cell which isn't empty meaning it has been chosen before --> move can't be made
        if (this->board[x][y] != ' ') {
            return false;
        }

    // the cell will be updated with the symbol if input is valid --> either X or O according to each player
    this->board[x][y] = toupper(symbol);
    // the number of moves will be incremented until it reaches 24 when the game ends
    this->n_moves++;
    return true;
}


template <typename T>
// displaying the board
void TicTacToeBoard<T> :: display_board() {

    // outputting a message for the user to tell him which move they are at
    cout << "\n --- The board at move " << this->n_moves << " ---\n";
    // output the column index numbers at the top for better visibility for the user
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

            //outputting the contents of each cell
            cout << this->board[i][j];
            //putting a separator between each column cell
            if (j < 4) cout << " | ";
        }
        cout << " |";
        cout << "\n";
        //putting a separator between each row
        if (i < 4) cout << "  ---------------------\n";
    }
    cout << endl;

}


// return true if 24 moves are done and no winner
template <typename T>
bool TicTacToeBoard<T>::is_draw() {
    return  (this->n_moves == 24 && !is_win());
}


// check if the game is over meaning that 24 moves have been done
template <typename T>
bool TicTacToeBoard<T>::game_is_over() {
    // either there is a winner or both players are draw
    return is_win() || is_draw();
}


// counting three-in-a-rows for each player
// will count for each player the three-in-a-rows in columns vertically, rows horizontally, and diagonally
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


template <typename T>
bool TicTacToeBoard<T>:: is_win(){
    int firstplayer = counter_three_in_a_row('X');
    int secondplayer = counter_three_in_a_row('O');
    if(this->n_moves == (24)){
        // player 1 wins
        if(firstplayer > secondplayer ){
            *global_Players[1] = *global_Players[0];
            return true;
        }

        if(firstplayer < secondplayer){
            return true;
        }
    }
    return false;
}



// constructor for tic Tac Toe player
template <typename T>
TicTacToePlayer<T>::TicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}


// Get move from a human player
template <typename T>
void TicTacToePlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlayer " << this-> getname() << ": Please enter the cell index you want separated with a space\n";
    cin >> x;
    cin >> y;
}

template <class T>
class Random_Player : public RandomPlayer<T> {
public:
        Random_Player(T symbol) : RandomPlayer<T>(symbol) {
            this->dimension = 5;
            this->name = "Random Computer Player";
            srand(static_cast<unsigned int>(time(0)));  // Seed the random generator
        }
        void getmove(int& x, int& y) override {
        // Random row (0 to 4)
        x = rand() % this->dimension;
        // Random column (0 to 4)
        y = rand() % 5;
        }

};

/*
~TicTacToe_des(){
    for(int i=o;i<this->rows;i++){
        delete [] this ->board;
    }
    delete [] board;
    global_Players[0] = nullptr;
    global_Players[1] = nullptr;
}
*/

#endif //BOARD_GAMES_TICTACTOE_H
