/*
* player.hpp - Header file for the Player class
 * Author: Ryan Godburn & Arjun Aravind
 * Date: 1/31/25
 * Description: This header file defines the Player class used in the game.
 *              It manages player attributes including name, color, and game
 *              progress, providing methods for gameplay actions and status
 *              reporting.
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "tools.hpp"
#include "enums.hpp"

class player {
private:
    string name;       // Player's name (no spaces)
    ECcolor pcolor;    // Player's color
    int wins;         // Number of columns captured
    int board[3];     // Captured columns

public:
    // Constructor
    player(string name, ECcolor color);

    // Destructor
    ~player() = default;

    // Accessors
    ECcolor color() const { return pcolor; }
    int score() const { return wins; }

    // Game actions
    // Records a won column and checks for game victory
    bool wonColumn(int colNum);

    // Output
    ostream& print(ostream& out);
};

// Stream operator for player output
inline ostream& operator<<(ostream& out, player& player) {
    return player.print(out);
}

#endif