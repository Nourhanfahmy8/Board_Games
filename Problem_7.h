#ifndef BOARD_GAMES_PROBLEM_7_H
#define BOARD_GAMES_PROBLEM_7_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>

/// Problem 7: 4*4 Tic Tac Toe ///


/// class of 4x4 Tic Tac Toe
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


/// Tic Tac Toe player class
template <typename T>
class Four_times_Four_Player : public Player <T>{
public:
    Four_times_Four_Player(string name, T symbol);
    void getmove(int &x, int&y);
};


/// Tic Tac Toe random player class
template <typename T>
class Random_fourtimesfour : public RandomPlayer <T>{
public:
    Random_fourtimesfour(T symbol);
    void getmove(int& x,int& y);
};



/*----------- IMPLEMENTATION -----------*/


/// random player initialization
template <class T>
Random_fourtimesfour<T> :: Random_fourtimesfour(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random generator
}

/// getting a random move from the random computer player
template <typename T>
void Random_fourtimesfour<T>::getmove(int& x, int& y) {
    // Random row index
    x = rand() % this->dimension;
    // Random column index
    y = rand() % this->dimension;
}

/// initializing the board of the game with empty spaces
template <typename T>
// initialize the board with empty spaces
Four_times_Four_Board <T>::Four_times_Four_Board(){

    this -> rows = 4;
    this-> columns = 4;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            // initialize the tokens of 'O', player 2 in their initial position
            if((i==0 && j == 0) || (i==0 && j == 2) || (i==3 && j == 1) || (i==3 && j == 3)){
                this->board[i][j] = 'O';
            }
                // initialize the tokens of 'X', player 1 in their initial position
            else if((i==0 && j == 1) || (i==0 && j == 3) || (i==3 && j == 0) || (i==3 && j == 2)){
                this->board[i][j] = 'X';

            }else{
                // initialize the rest of the cells with empty space
                this->board[i][j] = ' ';
            }
        }
    }
    // initialize the number of moves to be equal 0, it is output to the user to know how many turns have they played
    this->n_moves = 0;
}

/// updating the board after each players turn after validation
template <typename T>
bool Four_times_Four_Board<T>::update_board(int x, int y, T symbol) {

    // store the current token cell the user wants to move
    int CurrentX, CurrentY;

    // Determine whose turn it is --> if player 1 (even moves) or player 2 (odd moves)
    // even moves so player 1's turn
    if (this->n_moves % 2 == 0) {
        // player 1 is a human
        if (!israndom_player1) {

            //cout << "\n-> Player '1' : Please enter the cell index of the token you want to move (x y):\n";
            while (true) {
                // getting the current cell index
                cin >> CurrentX >> CurrentY;
                // validation check on the input

                if (cin.fail() || CurrentX < 0 || CurrentX >= 4 || CurrentY < 0 || CurrentY >= 4) {
                    cerr << "\nInvalid input! Please input a valid cell index between 0 and 3 inclusive\n" << endl;
                    cin.clear();          // Clear the input stream
                    cin.ignore(1000, '\n'); // Ignore remaining input
                    continue;
                } else if (this->board[CurrentX][CurrentY] != symbol) {
                    // The player chooses a cell that doesn't contain his symbol --> so current cell cant be chosen
                    cerr << "\nInvalid chosen cell, you have to choose a cell containing your token\n";
                    continue;

                } else break;
            }

            // getting the index the player wants to move the tokens to
            cout << "\n-> Now please enter the target position you want to move the token to (x y):\n";
            cout << "** Note: The move must be adjacent (horizontal or vertical)\n";

            while (true) {
                cin >> x >> y;
                // validation check on the input

                if (cin.fail() || x < 0 || x >= 4 || y < 0 || y >= 4) {
                    cerr << "\nInvalid input! Please input a valid cell index between 0 and 3 inclusive\n" << endl;
                    cin.clear();          // Clear the input stream
                    cin.ignore(1000, '\n'); // Ignore remaining input
                    continue;
                } else if (this->board[x][y] != ' ') {
                    // The user chooses a cell which isn't empty meaning --> move can't be made
                    cerr << "\nThis cell has already been chosen, Please choose another cell\n";
                    continue;
                }

                // validation check to make sure the move is adjacent (horizontal or vertical)
                if ((abs(CurrentX - x) == 1 && CurrentY == y) || (abs(CurrentY - y) == 1 && CurrentX == x)) {
                    // if yes, the move will be stored
                    break;
                } else {
                    cerr << "\nInvalid move, please choose another cell as you can only move to adjacent cells horizontally or vertically\n";
                    continue;
                }
            }

            // else Player 1 is random
        } else {

            // getting a random current index for player one
            do {
                CurrentX = rand() % 4;
                CurrentY = rand() % 4;
                // validation check to make sure the index chosen randomly is the same symbol for Player 1 -> 'X'
            } while (this->board[CurrentX][CurrentY] != symbol);

            // getting the random target position index
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

            //cout << "\n-> Player '2' : Please enter the cell index of the token you want to move (x y):\n";
            while (true) {
                // getting the current cell index
                cin >> CurrentX >> CurrentY;
                // validation check on the input

                if (cin.fail() || CurrentX < 0 || CurrentX >= 4 || CurrentY < 0 || CurrentY >= 4) {
                    cerr << "\nInvalid input! Please input a valid cell index between 0 and 3 inclusive\n" << endl;
                    cin.clear();          // Clear the input stream
                    cin.ignore(1000, '\n'); // Ignore remaining input
                    continue;
                } else if (this->board[CurrentX][CurrentY] != symbol) {
                    // The player chooses a cell that doesn't contain his symbol --> so current cell cant be chosen
                    cerr << "\nInvalid chosen cell, you have to choose a cell containing your token\n";
                } else break;
            }

            // getting the index the player wants to move the tokens to
            cout << "\n-> Now please enter the target position you want to move the token to (x y):\n";
            cout << "** Note: The move must be adjacent (horizontal or vertical)\n";
            while (true) {
                cin >> x >> y;
                // validation check on the input
                if (cin.fail() || x < 0 || x >= 4 || y < 0 || y >= 4) {
                    cerr << "\nInvalid input! Please input a valid cell index between 0 and 4 inclusive\n" << endl;
                    cin.clear();          // Clear the input stream
                    cin.ignore(1000, '\n'); // Ignore remaining input
                    continue;
                } else if (this->board[x][y] != ' ') {
                    // The user chooses a cell which isn't empty meaning --> move can't be made
                    cerr << "\nThis cell has already been chosen, Please choose another cell\n";
                }

                // validation check to make sure the move is adjacent (horizontal or vertical)
                if ((abs(CurrentX - x) == 1 && CurrentY == y) || (abs(CurrentY - y) == 1 && CurrentX == x)) {
                    // if yes, the move will be stored
                    break;
                } else {
                    cerr << "\nInvalid move, please choose another cell as you can only move to adjacent cells horizontally or vertically\n";
                    continue;
                }
            }


            // player 2 is a random player
        } else {
            // getting the random target position index
            do {
                CurrentX = rand() % 4;
                CurrentY = rand() % 4;
                // validation check to make sure the index chosen randomly is the same symbol for Player 2 -> 'O'
            } while (this->board[CurrentX][CurrentY] != symbol);

            // getting the random target position index
            do {
                x = rand() % 4;
                y = rand() % 4;
                // validation check that the chosen cell is empty and adjacent vertically or horizontally

            } while (this->board[x][y] != ' ' || !((abs(CurrentX - x) == 1 && CurrentY == y) || (abs(CurrentY - y) == 1 && CurrentX == x)));  // Ensure adjacency and empty cell
        }
    }

    // Clear the current position
    this->board[CurrentX][CurrentY] = ' ';
    // Place the player's token at the new position
    this->board[x][y] = toupper(symbol);
    // Increment the number of moves to give good counter visibility for the player
    this->n_moves++;
    return true;
}

/// display the board after each move
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
    cout << "  -----------------\n";
    cout << endl;

}


/// counting three-in-a-rows for each player
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

/// check if there is a winner
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


/// there is now draw in the game, so the is draw is always false
template <typename T>
bool Four_times_Four_Board<T>::is_draw() {
    return  false;
}

/// check if the game is over meaning that a player has won
template <typename T>
bool Four_times_Four_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


/// constructor for tic Tac Toe player
template <typename T>
Four_times_Four_Player<T>::Four_times_Four_Player(string name, T symbol) : Player<T>(name, symbol) {}



/// Get move from a human player
template <typename T>
void Four_times_Four_Player<T>::getmove(int& x, int& y) {
    // get move is implemented in the update board
    cout << "\n-> Player '" << this->getname() << "' : Please enter the cell index of the token you want to move (x y):\n";

}

#endif // BOARD_GAMES_PROBLEM_7_H