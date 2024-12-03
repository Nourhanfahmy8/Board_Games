#ifndef BOARD_GAMES_MISERETICTACTOE_H
#define BOARD_GAMES_MISERETICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>

// class of Tic Tac Toe
template <typename T>
class MisereTicTacToeBoard: public Board<T> {
public:
    MisereTicTacToeBoard();
    bool update_board(int x,int y,T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    int counter_three_in_a_row(T symbol);
};


// Tic Tac Toe player class
template <typename T>
class MisereTicTacToePlayer : public Player <T>{
public:
    MisereTicTacToePlayer(string name, T symbol);
    void getmove(int &x, int&y);
};


// Tic Tac Toe random player
template <typename T>
class MisereTicTacToeRandomPlayer : public RandomPlayer <T>{
public:
    MisereTicTacToeRandomPlayer(T symbol);
    void getmove(int& x,int& y);
};




/*----------------------- IMPLEMENTATION -----------------------*/
template <typename T>
MisereTicTacToeBoard <T>::MisereTicTacToeBoard(){
    this -> rows = 3;
    this-> columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

template <typename T>
// updating the board with each input move by the computer player or the user
bool MisereTicTacToeBoard<T> :: update_board(int x, int y, T symbol){

    // if the user inputs a row index less than 0 or greater than 2 --> out of bounds
    // or if the user inputs a column index less than 0 or greater than 2 --> out of bounds
    // or if the user chooses a cell which isn't empty --> move can't be made
    if (x < 0 || x >= 3 || y < 0 || y >= 3 || this->board[x][y] != ' ') {
        cout << "\n--> Invalid input!! Please input another cell\n";
        return false; // Invalid move
    }

    // the cell will be updated with the symbol --> either X or O according to each player
    this->board[x][y] = toupper(symbol);
    // the number of moves will be incremented until it reaches 9 when the game ends
    this->n_moves++;
    return true;
}


template <typename T>
void MisereTicTacToeBoard<T> :: display_board() {

    // output the column index numbers at the top for better visibility
    cout << "    ";
    for(int x=0;x<3;x++){
        cout  << x << "   ";
    }
    cout << endl;

    // output the grid
    for (int i = 0; i < 3; i++) {
        // output the row index number for better visibility for the user
        cout << i << " | ";
        for (int j = 0; j < 3; j++) {

            //outputting the contents of each cell
            cout << this->board[i][j];
            //putting a separator between each column cell
            if (j < 2) cout << " | ";
        }
        cout << " |";
        cout << "\n";
        //putting a separator between each row
        if (i < 2) cout << "  -------------\n";
    }
    cout << endl;

}

// return true if 9 moves are done and no winner
template <typename T>
bool MisereTicTacToeBoard<T>::is_draw() {
    return  (this->n_moves == 9 && !is_win());
}


// check if the game is over
template <typename T>
bool MisereTicTacToeBoard<T>::game_is_over() {
    //return this-> n_moves == 9;
    return is_win() || is_draw();
}







// counting three-in-a-rows for each player
// will count for each player the three-in-a-rows in columns vertically, rows horizontally, and diagonally
template <typename T>
int MisereTicTacToeBoard<T>::counter_three_in_a_row(T symbol) {
    int counter = 0;

    // checking horizontally for three in a row in rows
    for (int i = 0; i < this->rows; i++) {
        // counting for 3 cells only each time, so will only check for 3 columns everytime
        for (int j = 0; j<= this->columns-3; j++) {

            // if the 3 cells next to each other are the same symbol, the counter will be incremented
            if ( (this->board[i][j] == symbol) && (this->board[i][j + 1] == symbol) && (this->board[i][j + 2] == symbol)) {
                counter++;
            }
        }
    }

    // Check vertically for three in a row in columns
    for (int j = 0; j < this->columns; j++) {
        // will only check for 3 cells each time, so will only check for 3 row cells each time
        for (int i = 0; i <= this->rows-3; i++) {

            // if the 3 cells below each other are the same symbol, the counter will be incremented
            if ( (this->board[i][j] == symbol) && (this->board[i + 1][j] == symbol) && (this->board[i + 2][j] == symbol)) {
                counter++;
            }
        }
    }


    // Checking diagonals for each cell from left and right
    // only check 3 cells, so for 3 rows and 3 columns each time
    for (int i = 0; i <= this->rows- 3; i++) {
        for (int j = 0; j <= this->columns- 3; j++) {

            if ( (this->board[i][j] == symbol) && (this->board[i + 1][j + 1] == symbol) && (this->board[i + 2][j + 2] == symbol)) {
                counter++;
            }
        }
    }

    // Check diagonals (right to left)
    for (int i = 0; i <= this->rows- 3; i++) {
        for (int j = 2; j < this->columns; j++) {

            // checking the diagonal cells
            if ( (this->board[i][j] == symbol && this->board[i + 1][j - 1]) == symbol && (this->board[i + 2][j - 2] == symbol)) {
                counter++;
            }
        }
    }

    return counter;
}




template <typename T>
bool MisereTicTacToeBoard<T>:: is_win(){
    //int firstplayer = ;
    //int secondplayer = counter_three_in_a_row('O');

    // player 1 loses, player 2 wins
        if(counter_three_in_a_row('X') > 0 && counter_three_in_a_row('O') == 0){
            return true;
        }

        // player 2 loses, player 1 wins
        if(counter_three_in_a_row('O') > 0 ){
            return true;
        }
    return false;
}





// constructor for tic Tac Toe player
template <typename T>
MisereTicTacToePlayer<T>::MisereTicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}


// Get move from a human player
template <typename T>
void MisereTicTacToePlayer<T>::getmove(int& x, int& y) {
    cout << "Please enter the cell index you want separated with a space\n";
    cin >> x;
    cin >> y;
}

template <typename T>
MisereTicTacToeRandomPlayer<T>::MisereTicTacToeRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

// Generate a random move
template <typename T>
void MisereTicTacToeRandomPlayer<T>::getmove(int& x, int& y) {
    do {
        x = rand() % 5;
        y = rand() % 5;
    }while (this->boardPtr->update_board(x, y, this->getsymbol()) == false);
}

#endif //BOARD_GAMES_MISERETICTACTOE_H
