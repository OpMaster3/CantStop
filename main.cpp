/*
* main.cpp - A test program for the Game & Board class.
 * Author: Ryan Godburn & Arjun Aravind
 * Date: 2/25/25
 * Description: This program tests the Game class and board class
 *              by writing results to a file and printing them to
 *              the console.
 */

// Libraries
#include "dice.hpp"
#include "player.hpp"
#include "enums.hpp"
#include "column.hpp"
#include "game.hpp"

// Function prototypes for unit tests
void unitDice();
void unitPlayer();
void unitColumn();
void unitBoard();

// Main function
int main() {
    srand(time(NULL));
    banner();

    // Create game instance and play one turn
    Game game;

    // Play one turn with the current player (which is tracked inside Game)
    game.oneTurn();

    bye();
    return 0;
}