#ifndef BOARD_GAMES_PROBLEM_7_H
#define BOARD_GAMES_PROBLEM_7_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>


// class of 4x4 Tic Tac Toe
template <typename T>
class Four_times_Four_Board: public Board<T>{
public:
    Four_times_Four_Board();
    bool update_board(int x,int y,T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    int counter_three_in_a_row(T symbol);
};


// Tic Tac Toe player class
template <typename T>
class Four_times_Four_Player : public Player <T>{
public:
    Four_times_Four_Player(string name, T symbol);
    void getmove(int &x, int&y);
};


// Tic Tac Toe random player
template <typename T>
class Random : public Random_Player <T>{
public:
    Random(T symbol);
    void getmove(int& x,int& y);
};




/*----------------------- IMPLEMENTATION -----------------------*/

template <typename T>
// initialize the board with empty spaces
Four_times_Four_Board <T>::Four_times_Four_Board(){
    this -> rows = 4;
    this-> columns = 4;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            // initialize the tokens of 'x', player 1 in their initial position
            if((i==0 && j == 0) || (i==0 && j == 2) || (i==3 && j == 1) || (i==3 && j == 3)){
                this->board[i][j] = 'O';
            }
            // initialize the tokens of 'O', player 2 in their initial position
            else if((i==0 && j == 1) || (i==0 && j == 3) || (i==3 && j == 0) || (i==3 && j == 2)){
                this->board[i][j] = 'X';

            }else{
                // initialize the rest of the cells with empty space
                this->board[i][j] = ' ';
            }
        }
    }
    // initialize the number of moves to be equal 0, to output it for the player
    this->n_moves = 0;
}


template <typename T>
bool Four_times_Four_Board<T>::update_board(int x, int y, T symbol) {
    int CurrentX, CurrentY;

    cout << "\n-> Enter the token's current position (row and column) that you want to move: \n";
    // inputting the index position of the current values of X or O
    cin >> CurrentX >> CurrentY;

    // validation check to make sure the current token input and the new position input are both within the bounds
    if (CurrentX < 0 ||  CurrentX>= this->rows ||  CurrentY < 0 ||  CurrentY >= this->columns ||
        x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false;
    }

    // check if the current input token is equal to the symbol of the player, if not then the input is invalid
    if (this->board[CurrentX][ CurrentY] != symbol) {
        cout << "\n^^ Invalid input token, you must move your own token. ^^\n";
        return false;
    }

    // if the input cell is not empty, this means the cell is already occupied
    if (this->board[x][y] != ' ') {
        cout << "\n^^ Invalid move, the cell is not empty ^^\n";
        return false;
    }

    // getting absolute difference of the input token cell and new cell position
    // if the difference is equal to 1, then the 2 input points are either vertically above each other or horizontally next to each other
    // if the difference isn't equal to 1 then the input is not valid
    if (!((abs(CurrentX - x) == 1 &&  CurrentY == y) || (abs( CurrentY - y) == 1 && CurrentX == x))) {
        cout << "\n^^ Invalid move, you can only move to adjacent cells horizontally or vertically ^^\n";
        return false;
    }

    // making the current token empty
    this->board[CurrentX][CurrentY] = ' ';
    // making the new cell with the symbol of the player
    this->board[x][y] = toupper(symbol);
    this->n_moves++;
    return true;
}



template <typename T>
// displaying the board
void Four_times_Four_Board<T> :: display_board() {

    // outputting a message for the user to tell him which move they are at
    cout << "\n --- The board at move " << this->n_moves << " ---\n";
    // output the column index numbers at the top for better visibility for the user
    cout << "    ";
    for(int x=0;x<4;x++){
        cout  << x << "   ";
    }
    cout << endl;

    // output the grid
    for (int i = 0; i < 4; i++) {
        // output the row index number for better visibility for the user
        cout << i << " | ";
        for (int j = 0; j < 4; j++) {

            //outputting the contents of each cell
            cout << this->board[i][j];
            //putting a separator between each column cell
            if (j < 3) cout << " | ";
        }
        cout << " |";
        cout << "\n";
        //putting a separator between each row
        if (i < 3) cout << "  -----------------\n";
    }
    cout << endl;

}


// counting three-in-a-rows for each player
// will count for each player the three-in-a-rows in columns vertically and horizontally
template <typename T>
int Four_times_Four_Board<T>::counter_three_in_a_row(T symbol) {
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

    return counter;
}


template <typename T>
bool Four_times_Four_Board<T>:: is_win(){
    int first = counter_three_in_a_row('X');
    int second = counter_three_in_a_row('O');
    // first player has a three in a row and second player doesn't
    // So first player won
    if(first > 0){
        *global_Players[1] = *global_Players[0];
        return true;
    }
    // second player won
    else if(second>0){
        *global_Players[1] = *global_Players[1];
        return true;
    }
    return false;
}


// there is now draw in the game, so the is draw is always false
template <typename T>
bool Four_times_Four_Board<T>::is_draw() {
    return  false;
}


// check if the game is over meaning that a player has won
template <typename T>
bool Four_times_Four_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


// constructor for tic Tac Toe player
template <typename T>
Four_times_Four_Player<T>::Four_times_Four_Player(string name, T symbol) : Player<T>(name, symbol) {}



// Get move from a human player
template <typename T>
void Four_times_Four_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlayer " << this-> getname() << ": Please enter the cell index you want separated with a space\n";
    cin >> x;
    cin >> y;
}


template <class T>
class Random_fourtimesfour : public RandomPlayer<T> {
public:
    Random_fourtimesfour(T symbol) : RandomPlayer<T>(symbol) {
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







#endif //BOARD_GAMES_PROBLEM_7_H
