#ifndef Numerical_XO_H
#define Numerical_XO_H
#include "BoardGame_Classes.h"
#include<limits>


/// Problem 5: Numericat Tic Tac Toe ///


// NumericalBoard: A specialized board for the Numerical Tic-Tac-Toe game.
template <typename T>
class NumericalBoard: public Board<T>{
public:
    NumericalBoard();
    bool update_board(int x, int y, T symbol) ;
    void display_board() ;
    bool is_win() ;
    bool is_draw() ;
    bool game_is_over();
};
// NumericalPlayer: A player for Numerical Tic-Tac-Toe that ensures odd/even constraints.
template <typename T>
class NumericalPlayer: public Player<T>{
private:
    vector<int> used_nums;// Keeps track of numbers already used by the player.
    bool used(int num);    // Checks if a number has already been used.
    bool valid_num(int num); // Validates if the number is valid (odd/even depending on the player).

public :
    NumericalPlayer(string name , T symbol) ;
    void getmove(int& x , int& y) ;
};
// Numerical_Random_Player: A random player for Numerical Tic-Tac-Toe with odd/even constraints.
template <typename T>
class Numerical_Random_Player : public RandomPlayer<T>{
private:
    vector<int> used_nums;
    bool used(int num);
    bool valid_num(int num);
   vector<int> availableNumbers;

public:
    Numerical_Random_Player(T symbol);
    void getmove(int &x, int &y);

};
//--------------------------------------- IMPLEMENTATION
#include <iostream>
#include <iomanip>
using namespace std;
// Constructor for NumericalBoard: Initializes a 3x3 board with all cells set to 0.
template <typename T>
NumericalBoard<T>::NumericalBoard() {
    this->rows = this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0; // Initialize all cells to 0
        }
    }
    this->n_moves = 0; // Initialize move count to 0
}
template <typename T>
// Updates the board with the given number if the move is valid.
bool NumericalBoard<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (x >= 0 &&  x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0){
            this->n_moves++;
            this->board[x][y] = mark;
            return false;
    }
    return true;
}
// Displays the current state of the board.
template <typename T>
void NumericalBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}
// Checks for a win condition (sum of 15 in rows, columns, or diagonals).
template <typename T>
bool NumericalBoard<T>::is_win() {
    // Check rows for win
    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0) {
            if (this->board[i][0] + this->board[i][1] + this->board[i][2] == 15) {
                    return true;
            }
        }
    }
    // Check columns for win
    for (int i = 0; i < this->columns; i++) {
        if (this->board[0][i] != 0 && this->board[1][i] != 0 && this->board[2][i] != 0) {
            if (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15) {
                    return true;
            }
        }
    }
    // Check diagonals for win
    if (this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0) {
        if (this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) {
                return true;
        }
    }
    if (this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0) {
        if (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15) {
                return true;
        }
    }
    return false;
}

// Return true if 9 moves are done and no winner(Draw)
template <typename T>
bool NumericalBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}
// Checks if the game is over (win or draw).
template <typename T>
bool NumericalBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for Numerical_Player
template <typename T>
NumericalPlayer<T>::NumericalPlayer(string name, T symbol) : Player<T>(name, symbol) {}
//Validates if the number is odd or even based on the player's symbol.
template <typename T>
bool NumericalPlayer<T> ::valid_num(int num) {
    if(this-> symbol == 1){
        return num % 2 == 1;
    }
    else{
        return num % 2 == 0;
    }
}
template <typename T>
bool NumericalPlayer<T> ::used(int num) {
    for (int i = 0; i < used_nums.size(); i++) {
        if (used_nums[i] == num) {
            return true;
        }
    }
    return false;
}
// Gets the player's move and validates it.
template <typename T>
void NumericalPlayer<T>::getmove(int& x, int& y) {
    cout << "Entering getmove for " << this->getname() << endl;
    int num;
    bool move = false;
    while (!move) {
        cout << this->getname() << " (" << (this->symbol == 1 ? "Odd" : "Even")
             << "), enter your move(row,col): ";
        cin >> x >> y;
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter two integers for the row and column (0-2).\n";
            continue;
        }
        if (x < 0 || x >= 3 || y < 0 || y >= 3) {
            cout << "Invalid coordinates! Please enter values between 0 and 2.\n";
            continue;
        }
        cout << "Enter the number: ";
        cin >> num;
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter integar value.\n";
            continue;
        }
        if(num < 1 || num > 9){
            cout << "You must enter number between(1,9) "<< endl;
            continue;
        }
        if (!valid_num(num)) {
            cout << "Invalid number! You must enter an " << (this->symbol == 1 ? "odd" : "even")
                 << " number.\n";
            continue;
        }
        if (used(num)) {
            cout << "Number already used! Choose a different number.\n";
            continue;
        }
        if (this->boardPtr->update_board(x, y, num)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }
        used_nums.push_back(num);
        move = true;
    }
    cout << " Move successfully completed for " << this->getname() << endl;
}
template <typename T>
bool Numerical_Random_Player<T> ::valid_num(int num) {
    if(this-> symbol == 1){
        return num % 2 == 1;
    }
    else{
        return num % 2 == 0;
    }
}
template <typename T>
bool Numerical_Random_Player<T> ::used(int num) {
    for(int i = 0 ; i < used_nums.size() ; i++) {
        if (used_nums[i] == num){
            return true;
        }
    }
    return false;
}
// Constructor for Numerical_Random_Player
template <typename T>
Numerical_Random_Player<T>::Numerical_Random_Player(T symbol) : RandomPlayer<T>(symbol){
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    this->dimension = 3;
    this->name = "Random Computer Player";
    if(symbol % 2 != 0 ){
        availableNumbers ={1,3,5,7,9};
    }
    else{
        availableNumbers = {2,4,6,8};
    }
}
// Gets a random move for the player.
template <typename T>
void Numerical_Random_Player<T>::getmove(int& x, int& y){
    bool move = false;
    int number;
    while (!move) {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
         number = availableNumbers[rand() % availableNumbers.size()];
        if (used(number)) {
            continue;
        }
        if (!this->boardPtr->update_board(x, y, number)) {
            used_nums.push_back(number);
            move = true;
        }
    }
    cout << "The random number is : " << number << " at cell " << "("<< x << "," << y << ")"<< endl;
}
#endif //Numerical_XO_H
