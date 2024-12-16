#ifndef BOARD_GAMES_PROBLEM_9_H
#define BOARD_GAMES_PROBLEM_9_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>


/// Problem 9: SUS game ///

Player<char>* global_Players[2];
static bool israndom_player1 = false;
static bool israndom_player2 = false;

/// class of 3*3 SUS Tic Tac Toe
template <typename T>
class SUS_board: public Board<T> {
private:
    int nplayer1 = 0,nplayer2 = 0;
    bool rowCount[3] = {false , false , false}; // To count the 3 rows we can win by
    bool colCount[3] = {false , false , false}; // To count the 3 columns we can win by
    bool diagCount[2] = {false , false}; // To count the 2 diagonals we can win by
public:
    SUS_board();
    bool update_board(int x,int y,T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    void count_word();
};

/// Class of SUS Tic Tac Toe player
template <typename T>
class SUS_Player : public Player <T>{
public:
    SUS_Player(string name, T symbol);
    void getmove(int &x, int&y);
};

//---------- IMPLEMENTATION -----------/

/// initialize the board for the SUS tic tac toe with empty spaces
template <typename T>
// initialize the board with empty spaces
SUS_board <T>::SUS_board(){
    this -> rows = 3;
    this-> columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    // initialize the number of moves to 0
    // display it to the user for better visualization
    this->n_moves = 0;
    nplayer1 = 0;
    nplayer2 = 0;
}

/// validation check on the input and updating the board
template <typename T>
// updating the board with each input move by the computer player or the user
bool SUS_board<T> :: update_board(int x, int y, T symbol){

    // Check if it's Player 1's turn
    if (this->n_moves % 2 == 0) {
        nplayer1+=1;
        // Player 1
        if (!israndom_player1) {
            // Player 1 is a human
            // validation check on the input cell by the user
            while (true) {
                cin >> x >> y;
                // validation check on the input

                if (cin.fail() || x < 0 || x >= 3 || y < 0 || y >= 3) {
                    cerr << "\nInvalid input! Please input a valid cell index between 0 and 2 inclusive\n" << endl;
                    cin.clear();          // Clear the input stream
                    cin.ignore(1000, '\n'); // Ignore remaining input
                    continue;
                } else if (this->board[x][y] != ' ') {
                    // The user chooses a cell which isn't empty meaning it has been chosen before
                    cerr << "\nThis cell has already been chosen, Please choose another cell\n";
                } else break;
            }
            if(this->n_moves>=3){
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

            // validation check on the input
            while (true) {
                cin >> x >> y;

                if (cin.fail() || x < 0 || x >= 3 || y < 0 || y >= 3) {
                    cerr << "\nInvalid input! Please input a valid cell index between 0 and 2 inclusive\n" << endl;
                    cin.clear();          // Clear the input stream
                    cin.ignore(1000, '\n'); // Ignore remaining input
                    continue;
                } else if (this->board[x][y] != ' ') {
                    // The user chooses a cell which isn't empty
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

    // the cell will be updated with the symbol --> either S or O according to each player
    this->board[x][y] = toupper(symbol);
    // the number of moves will be incremented until it reaches 9 when the game ends
    this->n_moves++;
    return true;
}

/// display the board after each turn with the updated cell indecies
template <typename T>
void SUS_board<T> :: display_board() {

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
bool SUS_board<T>::is_draw() {
    // return true if 9 moves are done and no winner
    return  (this->n_moves == 9 && !is_win());
}


/// check if the game is over
template <typename T>
bool SUS_board<T>::game_is_over() {
    // either there is a winning player or the game is a draw
    return is_win() || is_draw();
}


/// counting the number SUS made for each player
template <typename T>
void SUS_board<T>::count_word() {

    // Check horizontally for three in a row in rows
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if ((this->board[i][j] == 'S') &&
                (this->board[i][j + 1] == 'U') &&
                (this->board[i][j + 2] == 'S') && !rowCount[i]) {
                if(this->n_moves % 2 == 0){
                    nplayer2++;
                } else {
                    nplayer1++;
                }
                rowCount[i] = true;
            }

        }
    }

    // Check vertically for three in a row in columns
    for (int j = 0; j < this->columns; j++) {
        for (int i = 0; i <= this->rows - 3; i++) {
            if ((this->board[i][j] == 'S') &&
                (this->board[i + 1][j] == 'U') &&
                (this->board[i + 2][j] == 'S') && !colCount[i]) {
                if (this->n_moves % 2 == 0) {
                    nplayer2++;
                } else {
                    nplayer1++;
                }
                colCount[i] = true;
            }


            // Check diagonals (\)
            if (this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S' && !diagCount[0]) {
                if (this->n_moves % 2 == 0) {
                    nplayer2++;
                } else {
                    nplayer1++;
                }
                diagCount[0] = true;
            }

            // Check diagonal (/)
            if (this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S' && !diagCount[1]) {
                if (this->n_moves % 2 == 0) {
                    nplayer2++;
                } else {
                    nplayer1++;
                }
                diagCount[1] = true;
            }
        }

    }
}

/// check if there is a winner
template <typename T>
bool SUS_board<T>:: is_win(){
    count_word();
    // getting the number of 3 in a rows for second payer
    if (this->n_moves == 9){
        if (nplayer1 < nplayer2) {
            *global_Players[0] = *global_Players[1];
            return true;
        }
        // second player won
        if (nplayer1 > nplayer2) {
            *global_Players[1] = *global_Players[0];
            return true;
        }
    }
    return false;
}


/// constructor for tic Tac Toe player
template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}


/// telling the player to input the cell index they want
template <typename T>
void SUS_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlayer '" << this-> getname() << "' : Please enter the cell index you want separated with a space\n";

}

/// random player class and implementation
template <class T>
class SUS_Random : public RandomPlayer<T> {
public:
    SUS_Random(T symbol) : RandomPlayer<T>(symbol) {
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

#endif // BOARD_GAMES_PROBLEM_9_H