#ifndef BOARD_GAMES_PROBLEM_7_H
#define BOARD_GAMES_PROBLEM_7_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>


// boolean flag for each player to check if the player is a random player or human player

static bool israndom_player1 = false;
static bool israndom_player2 = false;

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
class Random_fourtimesfour : public RandomPlayer <T>{
public:
    Random_fourtimesfour(T symbol);
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

    // store the current token cell the user wants to move
    int CurrentX, CurrentY;

    // Determine whose turn it is --> if player 1 (even moves) or player 2 (odd moves)

    // even moves so player 1's turn
    if (this->n_moves % 2 == 0) {
        // player 1 is a human
        if (!israndom_player1) {
            cout << "\n-> Player 1, please enter the cell index of the token you want to move (x y):\n";
            // getting the current cell index
            cin >> CurrentX >> CurrentY;
            // getting the index the player wants to move the tokens to
            cout << "\n-> Now please enter the target position you want to move the token to (x y):\n";
            cin >> x >> y;

            // else Player 1 is random
        } else {
            // getting a random current index for player one
            do {
                CurrentX = rand() % 4;
                CurrentY = rand() % 4;
                // validation check to make sure the index chosen randomly is the same symbol for Player 1 -> 'X'
            } while (this->board[CurrentX][CurrentY] != symbol);

            // getting the random target position
            do {
                x = rand() % 4;
                y = rand() % 4;
                // validation check that the chosen cell is empty and adjacent vertically or horizontally
            } while (this->board[x][y] != ' ' || !((abs(CurrentX - x) == 1 && CurrentY == y) || (abs(CurrentY - y) == 1 && CurrentX == x)));  // Ensure adjacency and empty cell
        }
    }
    // else player 2's turn
    else {
        // player 2 is a human
        if (!israndom_player2) {
            cout << "\n--> Player 2, please enter the cell index of the token you want to move (x y):\n";
            cin >> CurrentX >> CurrentY;
            cout << "\n-> Now please enter the target position you want to move the token to (x y):\n";
            cin >> x >> y;
            // player 2 is a random player
        } else {
            // getting the random target position
            do {
                CurrentX = rand() % 4;
                CurrentY = rand() % 4;
                // validation check to make sure the index chosen randomly is the same symbol for Player 2 -> 'O'
            } while (this->board[CurrentX][CurrentY] != symbol);

            // getting the random target position
            do {
                x = rand() % 4;
                y = rand() % 4;
                // validation check that the chosen cell is empty and adjacent vertically or horizontally

            } while (this->board[x][y] != ' ' || !((abs(CurrentX - x) == 1 && CurrentY == y) || (abs(CurrentY - y) == 1 && CurrentX == x)));  // Ensure adjacency and empty cell
        }
    }

    // Validate the indexes input by the player
    if (CurrentX < 0 || CurrentX >= this->rows || CurrentY < 0 || CurrentY >= this->columns ||
        x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        cout << "\n^^ Invalid move, the input is out of bounds\n";
        return false;
    }

    // Check if the player is trying to move their own symbol
    if (this->board[CurrentX][CurrentY] != symbol) {
        cout << "\nInvalid move, you can only move your own token\n";
        return false;
    }

    // Validation check to make sure that the target cell is empty
    if (this->board[x][y] != ' ') {
        cout << "\nInvalid move, target cell is not empty\n";
        return false;
    }

    // validation check to make sure the move is adjacent (horizontal or vertical)
    if ((abs(CurrentX - x) == 1 && CurrentY == y) || (abs(CurrentY - y) == 1 && CurrentX == x)) {
        // if yes, the move will be stored
        // Clear the current position
        this->board[CurrentX][CurrentY] = ' ';
        // Place the player's token at the new position
        this->board[x][y] = toupper(symbol);
        // Increment the number of moves to give good counter visibility for the player
        this->n_moves++;
        return true;
    } else {
        cout << "Invalid move, you can only move to adjacent cells horizontally or vertically\n";
        return false;
    }
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
    // Checking diagonally1
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] == symbol && this->board[i + 1][j + 1] == symbol && this->board[i + 2][j + 2] == symbol) {
                counter++;
            }
        }
    }

    // Checking diagonally2
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 2; j < this->columns; j++) { // Start from column 2 to ensure j-2 >= 0
            if (this->board[i][j] == symbol && this->board[i + 1][j - 1] == symbol && this->board[i + 2][j - 2] == symbol) {
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
    // get move is implemented in the update board
}

// random player initialization
template <class T>
Random_fourtimesfour<T> :: Random_fourtimesfour(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random generator
}

// getting a random move
template <typename T>
void Random_fourtimesfour<T>::getmove(int& x, int& y) {
    // Random row index
    x = rand() % this->dimension;
    // Random column index
    y = rand() % this->dimension;
}


#endif // BOARD_GAMES_PROBLEM_7_H