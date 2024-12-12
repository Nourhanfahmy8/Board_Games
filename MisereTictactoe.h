#ifndef BOARD_GAMES_MISERETICTACTOE_H
#define BOARD_GAMES_MISERETICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
//Player<char>* global_Players[2];
//static bool israndom_player1 = false;
//static bool israndom_player2 = false;
/// ----- PROBLEM 6 : Misere Tic Tac Toe ----- ///

/// class of 3*3 Misere Tic Tac Toe
template <typename T>
class MisereTicTacToeBoard: public Board<T> {
public:
    MisereTicTacToeBoard();
    bool update_board(int x,int y,T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    int count_three_in_a_row(T symbol);
};

/// Class of 3*3 Tic Tac Toe player class
template <typename T>
class MisereTicTacToePlayer : public Player <T>{
public:
    MisereTicTacToePlayer(string name, T symbol);
    void getmove(int &x, int&y);
};

/*---------- IMPLEMENTATION -----------*/

/// initialize the board for the misere tic tac toe with empty spaces
template <typename T>
// initialize the board with empty spaces
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
    // initialize the number of moves to 0, it is used to display to the user a counter of the number of turns played
    this->n_moves = 0;
}

/// updating the board with the input cell indicies by doing a validation check
template <typename T>
// updating the board with each input move by the computer player or the user
bool MisereTicTacToeBoard<T> :: update_board(int x, int y, T symbol){

    // Check if it's Player 1's turn
    if (this->n_moves % 2 == 0) {
        // Player 1
        if (!israndom_player1) {
            // Player 1 is a human

            // if the user inputs a row index less than 0 or greater than 2 --> out of bounds
            // or if the user inputs a column index less than 0 or greater than 2 --> out of bounds
            // or if the user chooses a cell which isn't empty --> move can't be made
            while (true) {
                cin >> x >> y;
                // validation check on the input

                if (cin.fail() || x < 0 || x >= 3 || y < 0 || y >= 3) {
                    cerr << "\nInvalid input! Please input a valid cell index between 0 and 2 inclusive\n" << endl;
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
                // Random row (0 to 2)
                x = rand() % 3;
                // Random column (0 to 2)
                y = rand() % 3;
            } while (this->board[x][y] != ' ');
        }
    } else {
        // Player 2
        if (!israndom_player2) {
            // player 2 is a human

            // if the user inputs a row index less than 0 or greater than 2 --> out of bounds
            // or if the user inputs a column index less than 0 or greater than 2 --> out of bounds
            // or if the user chooses a cell which isn't empty --> move can't be made
            while (true) {
                cin >> x >> y;
                // validation check on the input

                if (cin.fail() || x < 0 || x >= 3 || y < 0 || y >= 3) {
                    cerr << "\nInvalid input! Please input a valid cell index between 0 and 2 inclusive\n" << endl;
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
                // Random row (0 to 3)
                x = rand() % 3;
                // Random column (0 to 3)
                y = rand() % 3;
            } while (this->board[x][y] != ' ');
        }
    }

    // the cell will be updated with the symbol --> either X or O according to each player
    this->board[x][y] = toupper(symbol);
    // the number of moves will be incremented until it reaches 9 when the game ends
    this->n_moves++;
    return true;
}

/// display the board after each turn with the updated cell indecies
template <typename T>
void MisereTicTacToeBoard<T> :: display_board() {

    // outputting a message for the user to tell him which move they are at
    cout << "\n --- The board at move " << this->n_moves << " ---\n";
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
    cout << "  -------------\n";
    cout << endl;
}

/// Check if there is a winner
template <typename T>
bool MisereTicTacToeBoard<T>::is_draw() {
    // return true if 9 moves are done and no winner
    return  (this->n_moves == 9 && !is_win());
}


/// check if the game is over
template <typename T>
bool MisereTicTacToeBoard<T>::game_is_over() {
    // either there is a winning player or the game is a draw
    return is_win() || is_draw();
}


/// counting the number of three-in-a-rows for each player
// will count for each player the three-in-a-rows in columns vertically, rows horizontally, and diagonally
template <typename T>
int MisereTicTacToeBoard<T>::count_three_in_a_row(T symbol) {
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


/// check if there is a winner
/// the loser is the first player to reach 3 in a rows
template <typename T>
bool MisereTicTacToeBoard<T>:: is_win(){
    int first = count_three_in_a_row('X');
    int second = count_three_in_a_row('O');
    // first player has a three in a row and second player doesn't
    // So first player lost
    if(first > 0){
        *global_Players[0] = *global_Players[1];
        return true;
    }
    // second player lost and first player won
    if(second>0){
        *global_Players[1] = *global_Players[0];
        return true;
    }
    return false;
}

/// constructor for tic Tac Toe player
template <typename T>
MisereTicTacToePlayer<T>::MisereTicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}


/// telling the player to input the cell index they want
template <typename T>
void MisereTicTacToePlayer<T>::getmove(int& x, int& y) {
    cout << "Player '" << this->getname() << "' : Please enter the cell index you want separated with a space\n";

}

/// random player class and implementation
template <class T>
class Random_PlayerMisere : public RandomPlayer<T> {
public:
    Random_PlayerMisere(T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 3;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));  // Seed the random generator
    }
    void getmove(int& x, int& y) override {
        // Random row (0 to 2)
        x = rand() % this->dimension;
        // Random column (0 to 2)
        y = rand() % 3;
    }

};

#endif //BOARD_GAMES_MISERETICTACTOE_H