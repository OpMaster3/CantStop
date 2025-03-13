/*
* game.cpp - Implementation file for the Game class
 * Author: Ryan Godburn & Arjun Aravind
 * Date: 2/27/25
 * Description: This source file implements the Game class methods
 *              defined in game.hpp.
 */

#include "game.hpp"

// Constructor
Game::Game() {
    // Create game components using smart pointers
    dice = make_unique<Dice>(4);  // Create 4 dice

    // Initialize player
    cout << "Enter data for Player:\n";
    curPlayer = make_unique<player>(getNewPlayer());
}

// Get player info from keyboard with simplified input handling
player Game::getNewPlayer() {
    string name;
    int color;

    // Get player name - simplified
    cout << "Enter player name (no spaces): ";
    cin >> name;

    if(name.empty() || name.length() > 20) {
        cout << "Invalid name. Using default 'Player1'\n";
        name = "Player1";
    }

    // Get color choice - simplified without white option
    cout << "Enter color:\n"
         << "1 - Orange\n"
         << "2 - Yellow\n"
         << "3 - Green\n"
         << "4 - Blue\n"
         << "Choice: ";

    // Use direct input for numbers, no need for getline or exceptions
    cin >> color;

    // Validate input
    if(color < 1 || color > 4) {
        cout << "Invalid color. Using Orange.\n";
        color = 1;
    }

    return player(name, ECcolor(color));
}

// Execute one turn of the game - modified to use the internal curPlayer
void Game::oneTurn() {
    // Start the turn on the board using the current player
    board.startTurn(curPlayer.get());

    // Menu loop
    bool turnOver = false;
    while(!turnOver) {
        cout << "\n-- Turn Options --\n";
        cout << "1. Roll\n";
        cout << "2. Stop\n";
        cout << "3. Resign\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;

        switch(choice) {
            case 1: // Roll
            {
                // Roll the dice and get values
                const int* dvals = (*dice).roll();

                // Display dice with letters
                cout << "Dice: A=" << dvals[0] << ", B=" << dvals[1]
                     << ", C=" << dvals[2] << ", D=" << dvals[3] << endl;

                // Ask user for first pair
                cout << "Select two letters for first pair (e.g., AB): ";
                string pairInput;
                cin >> pairInput;

                // Validate input
                if(pairInput.length() != 2) {
                    cout << "Invalid input. Please enter exactly two letters.\n";
                    continue;
                }

                // Convert to uppercase
                pairInput[0] = toupper(pairInput[0]);
                pairInput[1] = toupper(pairInput[1]);

                // Validate letters
                if(pairInput[0] < 'A' || pairInput[0] > 'D' ||
                   pairInput[1] < 'A' || pairInput[1] > 'D' ||
                   pairInput[0] == pairInput[1]) {
                    cout << "Invalid dice selection. Please use A, B, C, or D without repeating.\n";
                    continue;
                }

                // Map letters to dice indices
                int Idx1 = pairInput[0] - 'A';
                int Idx2 = pairInput[1] - 'A';

                // Calculate first pair total
                int pair1 = dvals[Idx1] + dvals[Idx2];

                // Find the remaining two dice for second pair
                int Idx3 = -1, Idx4 = -1;
                for(int Idx = 0; Idx < 4; Idx++) {
                    if(Idx != Idx1 && Idx != Idx2) {
                        if(Idx3 == -1)
                            Idx3 = Idx;
                        else
                            Idx4 = Idx;
                    }
                }
                int pair2 = dvals[Idx3] + dvals[Idx4];

                cout << "First pair: " << pair1 << ", Second pair: " << pair2 << endl;

                // Validate column values before calling move
                bool move1Valid = (pair1 >= 2 && pair1 <= 12);
                bool move2Valid = (pair2 >= 2 && pair2 <= 12);

                // Try moves
                bool move1Success = move1Valid && board.move(pair1);
                cout << "Move to column " << pair1 << ": "
                     << (move1Success ? "Success" : "Failed") << endl;

                bool move2Success = move2Valid && board.move(pair2);
                cout << "Move to column " << pair2 << ": "
                     << (move2Success ? "Success" : "Failed") << endl;

                // Display board
                cout << board << endl;

                // Check for bust
                if(!move1Success && !move2Success) {
                    cout << "*** BUST! ***\n";
                    board.bust();
                    turnOver = true;
                }
                break;
            }
            case 2: // Stop
                board.stop();
                cout << "Turn ended, towers converted to tiles:\n";
                cout << board << endl;
                turnOver = true;
                break;
            case 3: // Resign (not fully implemented yet)
                cout << "Resign not implemented yet.\n";
                break;
            default:
                cout << "Invalid choice. Please select 1, 2, or 3.\n";
                // Clear input stream in case of invalid input
                cin.clear();
                cin.ignore(10000, '\n');
        }
    }
}