// File name:  A2_S21_Task2345_20230560_GroupB_20230172_20230119
// Team members: Nourhan Mohammed Ahmed (20230560), Salma Yasser Saied Abdelhalim (20230172), Habiba Mahmoud Mohamed Salem (20230119)

#include "BoardGame_Classes.h"
#include "Pyramid-X-O.h"
#include "Four-in-a-row.h"
#include "Tictactoe.h"
#include "Word-Tictactoe.h"
#include "Numerical_XO.h"
#include "MisereTictactoe.h"
#include "Problem_7.h"
#include "Problem_8.h"
#include "Problem_9.h"
#include <iostream>
#include <limits>

using namespace std;
//
//Player<char>* global_Players[2];
//static bool israndom_player1 = false;
//static bool israndom_player2 = false;

int main() {

    // Display the welcome message for the application
    cout << "\n===================Welcome to Tic-Tac-Toe Games Application===================\n\n";

    while (true) {
        // Display the list of game options to the user
        cout << "** Please choose which Tic Tac Toe Game you would like to play:-\n";
        cout << "1) Pyramid Tic-Tac-Toe.\n2) Four-in-a-row.\n3) 5 x 5 Tic-Tac-Toe.\n4) Word Tic-Tac-Toe."
                "\n5) Numerical Tic-Tac-Toe.\n6) Misere Tic-Tac-Toe."
                "\n7) 4x4 Tic-Tac-Toe.\n8) Ultimate Tic-Tac-Toe.\n9) SUS Tic-Tac-Toe.\n10) Exit.\n";

        int mainChoice;
        cin >> mainChoice;

        // Check for invalid input (non-numeric or out-of-range values)
        if (cin.fail()) {
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cerr << "\nInvalid input! Input choice must be from 1 to 9.\n";
            continue;
        }

        // Handle Pyramid Tic-Tac-Toe game
        if (mainChoice == 1) {
            int choice;
            Player<char>* players[2]; // Array to hold Player 1 and Player 2
            auto* board1 = new GameOne<char>(); // Create a board instance for Pyramid Tic-Tac-Toe
            cout << "\n*** Welcome to Pyramid Pyramid Tic Tac Toe Game :) ***\n";
            string player1Name, player2Name;

            // Setup Player 1
            cout << "-> Please enter Player 1's name: \n";
            cin >> player1Name;
            cout << "\nNow choose Player 1's type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {
                cin >> choice;

                // Handle invalid input for player type
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1) {
                    players[0] = new Human_Player<char>(player1Name, 'X'); // Create human player
                    break;
                } else if (choice == 2) {
                    players[0] = new Random_Player1<char>('X'); // Create random computer player
                    break;
                } else {
                    cerr << "\nInvalid choice! Please enter 1 or 2.\n";
                }
            }

            // Set up Player 1
            cout << "\n-> Please enter Player 2's name: \n";
            cin >> player2Name;
            cout << "\nNow choose Player 2's type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {

                cin >> choice;

                // Handle invalid input for player type
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1) {
                    players[1] = new Human_Player<char>(player2Name, 'O'); // Create human player
                    break;
                } else if (choice == 2) {
                    players[1] = new Random_Player1<char>('O'); // Create random computer player
                    break;
                } else {
                    cerr << "\nInvalid choice! Please enter 1 or 2.\n";
                }
            }

            // Create game manager and run the game
            GameManager<char> Game1(board1, players);
            cout << "\nGiving the Initial Board for this game...\n";
            Game1.run();

            // Clean up resources
            delete board1;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            cout << "====================================================\n";

        }else if (mainChoice == 2) {
            int choice;
            Player<char> *players[2];
            auto board2 = new FourInARowBoard<char>();
            cout << "\n*** Welcome to the Four-in-a-Row Game :) ***\n";
            string player1Name, player2Name;
            cout << "-> Please enter Player 1's name: \n";
            cin >> player1Name;
            cout << "\nNow choose Player 1's type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) { // Loop until valid input for Player 1 type

                cin >> choice;
                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1) {
                    players[0] = new FourInARowPlayer<char>(player1Name, 'X');// Create human player
                    break;
                } else if (choice == 2) {
                    players[0] = new FourInARowRandomPlayer<char>('X');// Create random player
                    break;
                } else {
                    cerr << "Invalid choice! Please enter 1 or 2.\n";
                }

            }
            // Set up Player 2 (O)
            cout << "-> Please enter Player 2's name: \n";
            cin >> player2Name;
            cout << "\nNow Choose Player 2 type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {

                cin >> choice;
                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }
                if (choice == 1) {
                    players[1] = new FourInARowPlayer<char>(player2Name, 'O');// Create human player
                    break;
                } else if (choice == 2) {
                    players[1] = new FourInARowRandomPlayer<char>('O');// Create random player
                    break;
                } else {
                    cerr << "Invalid choice! Please enter 1 or 2.\n";
                }
            }
            // Create the game manager and run the game
            GameManager<char> Game2 (board2, players);
            cout << "Giving the Initial Board for this game\n";
            Game2.run();

            // Clean up
            delete board2;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

            cout << "====================================================\n";
        }
        else if (mainChoice == 3) {
            int choice;
            Player<char>* players[2];
            auto* board3 = new TicTacToeBoard<char>();
            cout << "\n*** Welcome to the 5 x 5 Tic Tac Toe Game :) ***\n";
            string player1Name, player2Name;

            // Set up Player 1
            cout << "\n-> Please enter Player 1's name: \n";
            cin >> player1Name;
            cout << "\nNow choose Player 1's type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {

                cin >> choice;
                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1) {
                    players[0] = new TicTacToePlayer<char>(player1Name, 'X');// Create human player
                    break;
                } else if (choice == 2) {
                    players[0] = new Random_Player<char>('X');// Create random player
                    israndom_player1 = true;
                    break;
                } else {
                    cerr << "Invalid choice! Please enter 1 or 2.\n";
                }

            }

            // Set up Player 1
            cout << "\n-> Please enter Player 2's name: \n";
            cin >> player2Name;
            cout << "\nNow choose Player 2's type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {

                cin >> choice;
                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }
                if (choice == 1) {
                    players[1] = new TicTacToePlayer<char>(player2Name, 'O');// Create human player
                    break;
                } else if (choice == 2) {
                    players[1] = new Random_Player<char>('O');// Create random player
                    israndom_player2 = true;
                    break;
                } else {
                    cerr << "Invalid choice! Please enter 1 or 2.\n";
                }
            }

            // Create the game manager
            GameManager<char> Game3(board3, players);
            cout << "Giving the Initial Board for this game\n";
            global_Players[0] = players[0];
            global_Players[1] = players[1];
            Game3.run();

            // Clean up resources
            delete board3;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

            global_Players[0] = nullptr;
            global_Players[1]= nullptr;

            cout << "====================================================\n";
        }
        else if (mainChoice == 4){
            cout << "\n*** Ok, let's start playing the WORD game ;) ***\n";
            int choice;
            Player<char>* players[2];
            auto* board4 = new GameFour<char>();
            string player1Name, player2Name;

            // Set up Player 1
            cout << "-> Please enter Player 1's name:\n";
            cin >> player1Name;
            cout << "\nNow choose Player 1's type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {

                cin >> choice;
                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1) {
                    players[0] = new HumanPlayer<char>(player1Name, ' ');// Create human player
                    break;
                } else if (choice == 2) {
                    players[0] = new Random_Player4<char>(' ');// Create random player
                    break;
                } else {
                    cout << "Invalid choice! Please enter 1 or 2.\n";
                }

            }
            // Set up Player 2
            cout << "-> Please enter Player 2's name:\n";
            cin >> player2Name;
            cout << "\nNow choose Player 2's type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {

                cin >> choice;
                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1) {
                    players[1] = new HumanPlayer<char>(player2Name, ' ');// Create human player
                    break;
                } else if (choice == 2) {
                    players[1] = new Random_Player4<char>(' ');// Create random player
                    break;
                } else {
                    cerr << "Invalid choice! Please enter 1 or 2.\n";
                }

            }

            // Create the game manager and run the game
            GameManager<char> Game4(board4, players);
            cout << "Giving the Initial Board for this game\n";
            global_Players[0] = players[0];
            global_Players[1] = players[1];
            Game4.run();

            // Clean up resources
            delete board4;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            global_Players[0] = nullptr;
            global_Players[1]= nullptr;
            cout << "====================================================\n";
        }
        else if (mainChoice == 5){
            int choice;
            Player<int>* players[2];
            auto* board5 = new NumericalBoard<int>();
            string player1Name, player2Name;
            cout << "\n*** Welcome to the Numerical XO Game :) ***\n";

            // Player 1 setup
            cout << "-> Please enter Player 1's name : \n";
            cin >> player1Name;
            cout << "\nNow choose Player 1's type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) { // Loop until valid input for Player 1 type

                cin >> choice;

                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1) {
                    players[0] = new NumericalPlayer<int>(player1Name, 1);// Create human player
                    break;
                } else if (choice == 2) {
                    players[0] = new Numerical_Random_Player<int>(1);// Create random player
                    break;
                } else {
                    cerr << "Invalid choice! Please enter 1 or 2.\n";
                }
            }
            players[0]->setBoard(board5);

            // Player 2 setup
            cout << "\n-> Please enter Player 2's name : \n";
            cin >> player2Name;
            cout << "\nNow choose Player 2's type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) { // Loop until valid input for Player 2 type

                cin >> choice;

                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1) {
                    players[1] = new NumericalPlayer<int>(player2Name, 2);// Create human player
                    break;
                } else if (choice == 2) {
                    players[1] = new Numerical_Random_Player<int>(2);// Create random player
                    break;
                } else {
                    cerr << "Invalid choice! Please enter 1 or 2.\n";
                }
            }
            players[1]->setBoard(board5);

            // Run the game
            GameManager<int> Game5(board5, players);
            cout << "Giving the Initial Board for this game\n";
            Game5.run();

            // Cleanup
            delete board5;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            cout << "====================================================\n";
        }
        else if (mainChoice == 6){
            cout << "\n*** Welcome to the Misere Tic Tac Toe Game :) ***\n";
            int choice;
            Player<char>* players[2];
            auto* board6 = new MisereTicTacToeBoard<char>();
            string player1Name, player2Name;

            // Set up Player 1
            cout << "\n-> Please enter Player 1's name:\n";
            cin >> player1Name;
            cout << "\nNow choose Player 1's type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {

                cin >> choice;
                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1) {
                    players[0] = new MisereTicTacToePlayer<char>(player1Name, 'X');// Create human player
                    break;
                } else if (choice == 2) {
                    players[0] = new Random_PlayerMisere<char>('X');// Create random player
                    israndom_player1 = true;
                    break;
                } else {
                    cerr << "Invalid choice! Please enter 1 or 2.\n";
                }

            }
            // Set up Player 2
            cout << "-> Please enter Player 2's name:\n";
            cin >> player2Name;
            cout << "\nNow choose Player 2's type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {

                cin >> choice;
                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1) {
                    players[1] = new MisereTicTacToePlayer<char>(player2Name, 'O');// Create human player
                    break;
                } else if (choice == 2) {
                    players[1] = new Random_PlayerMisere<char>('O');// Create random player
                    israndom_player2 = true;
                    break;
                } else {
                    cerr << "Invalid choice! Please enter 1 or 2.\n";
                }

            }

            // Create the game manager and run the game
            GameManager<char> Game6(board6, players);
            global_Players[0] = players[0];
            global_Players[1] = players[1];

            cout << "Giving the Initial Board for this game\n";
            Game6.run();

            // Clean up resources
            delete board6;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            global_Players[0] = nullptr;
            global_Players[1]= nullptr;
            cout << "====================================================\n";
        }
        else if (mainChoice == 7){
            int choice;
            Player<char>* players[2];
            auto* board7 = new Four_times_Four_Board<char>();
            string player1Name, player2Name;
            cout << "\n*** Welcome to the 4 x 4 Tic Tac Toe Improved version of XO Game :) ***\n";

            // Set up player 1
            cout << "\n-> Please enter Player 1's name:\n";
            cin >> player1Name;
            cout << "\nNow choose Player 1 type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {

                cin >> choice;
                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1) {
                    players[0] = new Four_times_Four_Player<char>(player1Name, 'X');// Create human player
                    break;
                } else if (choice == 2) {
                    players[0] = new Random_fourtimesfour<char>('X');// Create random player
                    israndom_player1 = true;
                    break;
                } else {
                    cerr << "Invalid choice! Please enter 1 or 2.\n";
                }

            }
            // Set up Player 2
            cout << "\n-> Please enter Player 2 name:\n";
            cin >> player2Name;
            cout << "\nNow choose Player 2 type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {

                cin >> choice;
                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1) {
                    players[1] = new Four_times_Four_Player<char>(player2Name, 'O');// Create human player
                    break;
                } else if (choice == 2) {
                    players[1] = new Random_fourtimesfour<char>('O');// Create random player
                    israndom_player2= true;
                    break;
                } else {
                    cerr << "Invalid choice! Please enter 1 or 2.\n";
                }

            }

            // Create the game manager and run the game
            GameManager<char> Game7(board7, players);
            global_Players[0] = players[0];
            global_Players[1] = players[1];
            cout << "Giving the Initial Board for this game\n";
            Game7.run();
            // Clean up
            delete board7;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            global_Players[0] = nullptr;
            global_Players[1] = nullptr;
            cout << "====================================================\n";
        }
        else if (mainChoice == 8){
            int choice;
            Player<char>* players[2];
            auto* board8 = new Ultimate_Tic_Tac_Toe<char>();
            string player1Name, player2Name;
            cout << "\n*** Welcome to the Ultimate version of XO Game :) ***\n";

            // Set up player 1
            cout << "\n-> Please enter Player 1's name:\n";
            cin >> player1Name;
            cout << "\nNow choose Player 1's type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {

                cin >> choice;
                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1) {
                    players[0] = new Ultimate_Player<char>(player1Name, 'X');// Create human player
                    break;
                } else if (choice == 2) {
                    players[0] = new Random_Ultimate_Player<char>('X');// Create random player
                    israndom_player1 = true;
                    break;
                } else {
                    cerr << "Invalid choice! Please enter 1 or 2.\n";
                }

            }
            // Set up Player 2
            cout << "\n-> Please enter Player 2's name:\n";
            cin >> player2Name;
            cout << "\nNow choose Player 2's type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {

                cin >> choice;
                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1) {
                    players[1] = new Ultimate_Player<char>(player2Name, 'O');// Create human player
                    break;
                } else if (choice == 2) {
                    players[1] = new Random_Ultimate_Player<char>('O');// Create random player
                    israndom_player2 = true;
                    break;
                } else {
                    cerr << "Invalid choice! Please enter 1 or 2.\n";
                }

            }

            // Create the game manager and run the game
            GameManager<char> Game8 (board8, players);
            global_Players[0] = players[0];
            global_Players[1] = players[1];
            cout << "Giving the Initial Board for this game\n";
            Game8.run();
            // Clean up
            delete board8;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            global_Players[0] = nullptr;
            global_Players[1] = nullptr;
            cout << "====================================================\n";
        }
        else if (mainChoice == 9){
            int choice;
            Player<char>* players[2];
            auto* board9 = new SUS_board<char>();
            cout << "\n*** Welcome to the SUS Tic Tac Toe Game :) ***\n";
            string player1Name, player2Name;

            // Set up Player 1
            cout << "\n-> Please enter Player 1's name: \n";
            cin >> player1Name;
            cout << "\nNow choose Player 1's type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {

                cin >> choice;
                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }

                if (choice == 1) {
                    players[0] = new SUS_Player<char>(player1Name, 'S');// Create human player
                    break;
                } else if (choice == 2) {
                    players[0] = new SUS_Random<char>('S');// Create random player
                    israndom_player1 = true;
                    break;
                } else {
                    cerr << "Invalid choice! Please enter 1 or 2.\n";
                }

            }

            // Set up Player 1
            cout << "\n-> Please enter Player 2's name: \n";
            cin >> player2Name;
            cout << "\nNow choose Player 2's type:-\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {

                cin >> choice;
                if (cin.fail()) { // Check for invalid input (e.g., string)
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cerr << "Invalid input! Please enter 1 or 2.\n";
                    continue;
                }
                if (choice == 1) {
                    players[1] = new SUS_Player<char>(player2Name, 'U');// Create human player
                    break;
                } else if (choice == 2) {
                    players[1] = new SUS_Random<char>('U');// Create random player
                    israndom_player2 = true;
                    break;
                } else {
                    cerr << "Invalid choice! Please enter 1 or 2.\n";
                }
            }

            // Create the game manager
            GameManager<char> Game9(board9, players);
            cout << "Giving the Initial Board for this game\n";
            global_Players[0] = players[0];
            global_Players[1] = players[1];
            Game9.run();

            // Clean up resources
            delete board9;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

            global_Players[0] = nullptr;
            global_Players[1]= nullptr;

            cout << "====================================================\n";

        }
        else if (mainChoice == 10){
            cout << "*** Thank you for using the program, hope you enjoyed it :)\nGoodBye!\n";
            break;
        }
        else {
            cerr << "Invalid choice! Please enter a number between 1 and 10.\n\n";
        }
    }
    return 0;
}