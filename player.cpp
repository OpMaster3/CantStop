/*
* player.cpp - Implementation file for the Player class
 * Author: Ryan Godburn & Arjun Aravind
 * Date: 1/31/25
 * Description: This source file implements the Player class methods in
 *              player.hpp, including constructor, game actions, and
 *              output functions.
 */

#include "player.hpp"

// Constructor
player::player(string name, ECcolor color) : name(name),
                                             pcolor(color), wins(0) {}

// Record Win / Check Game Won
bool player::wonColumn(int colNum) {
    if(wins >= 3) return true;   // Already won
    board[wins++] = colNum;        // Update count and store column
    return wins == 3;            // Return true if won game
}

// Print values
ostream& player::print(ostream& out) {
    // Print the player's name, color, and score
    out << name << " (" << colorNames[(int)pcolor] << ") Score: " << wins;
    // If the player has won any games, print the columns of the wins
    if(wins > 0) {
        out << " Columns:";
        for(int Idx = 0; Idx < wins; Idx++)
            out << " " << board[Idx];  // Print column where player won
    }
    return out;
}
