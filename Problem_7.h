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
    void get_tokenposition(int& x, int& y);
    int counter_three_in_a_row(T symbol);
};


// Tic Tac Toe player class
template <typename T>
class Four_times_Four_Player : public Player <T>{
public:
    Four_times_Four_Player(string name, T symbol);
    void getmove(int &x, int&y);
    void get_tokenposition(int& x, int& y);
};


// Tic Tac Toe random player
template <typename T>
class Random : public Random_Player <T>{
public:
    Random(T symbol);
    void getmove(int& x,int& y);
    void get_tokenmove(int& x, int& y);
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
            if((i==0 && j == 0) || (i==0 && j == 2) || (i==3 && j == 1) || (i==3 && j == 3)){
                this->board[i][j] = 'O';
            }
            else if((i==0 && j == 1) || (i==0 && j == 3) || (i==3 && j == 0) || (i==3 && j == 2)){
                this->board[i][j] = 'X';

            }else{
                this->board[i][j] = ' ';
            }
        }
    }
    // initialize the number of moves to be equal 0
    this->n_moves = 0;
}

template <typename T>
// updating the board with each input move by the computer player or the user
bool Four_times_Four_Board<T> :: update_board(int x, int y, T symbol){

    // player 1's turn
    if(symbol =='X') {

        // if the user inputs a row index less than 0 or greater than 4 --> out of bounds
        // or if the user inputs a column index less than 0 or greater than 4 --> out of bounds
        if (x < 0 || x >= 5 || y < 0 || y >= 5) {
            return false;
        }
        // The user chooses a cell which isn't empty meaning it has been chosen before --> move can't be made
        if (this->board[x][y] != ' ') {
            return false;
        }

    }


    // the cell will be updated with the symbol if input is valid --> either X or O according to each player
    this->board[x][y] = toupper(symbol);
    // the number of moves will be incremented until it reaches 24 when the game ends
    this->n_moves++;
    return true;
}







// constructor for tic Tac Toe player
template <typename T>
Four_times_Four_Player<T>::Four_times_Four_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Get move from a human player
// getting the token the user wants to move
template <typename T>
void Four_times_Four_Player<T>::get_tokenposition(int& x, int& y) {
    // player 1's turn
    if(this-> getsymbol() == "X"){
        cout << "\nPlayer " << this-> getname() << ": Please enter the cell index of the token you want to move separated with a space\n";
        cin >> x;
        cin >> y;
    }

}



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
