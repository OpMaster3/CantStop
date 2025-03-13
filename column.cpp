/*
* column.cpp - Implementation file for the Column class.
 * Author: Ryan Godburn & Arjun Aravind
 * Date: 2/5/25
 * Description: This source file implements the methods in Column.hpp.
 *              It includes methods for managing tower placement, movement,
 *              and column capture in the game.
 */

#include "column.hpp"

// Column lengths table
const int Column::lens[13] = {
    0, 0, 3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3
};

// Constructor
Column::Column(int n) : num(n) {
    // No need to validate column number - it comes from Board class
    // No need to initialize cstate (done in header)
    // No need to initialize pos array (done in header)

    // Store column length as a member variable for easier access
    columnLength = lens[num];
}

// Start tower placement
bool Column::startTower(player* p) {
    // Can't place tower if column is already captured
    if(cstate == ECstate::capt) return false;

    // Get player's color index to check their current position
    int Idx = (int)p->color();
    if(pos[Idx] == 0) pos[0] = 1;  // No tile yet, place tower at start
    else pos[0] = pos[Idx] + 1;  // Place tower one space after player's tile

    // Check if tower position exceeds column length and update state
    if(pos[0] > columnLength) return false;

    // If tower reaches end, column becomes pending
    if(pos[0] == columnLength) cstate = ECstate::pend;

    // Tower placed successfully
    return true;
}

// Move tower forward
bool Column::move() {
    // Can't move if column captured or pending or no tower present
    if(cstate == ECstate::capt || cstate == ECstate::pend || pos[0] == 0) return false;

    // Advance tower one position and check if it exceeds column length
    if(++pos[0] > columnLength) return false;

    // If tower reaches end, column becomes pending
    if(pos[0] == columnLength) cstate = ECstate::pend;

    // Move completed successfully
    return true;
}

// Stop turn and convert tower
void Column::stop(player* p) {
    // If no tower present, nothing to convert
    if(pos[0] == 0) return;

    // Get player's color index
    int Idx = (int)p->color();
    // Replace player's old tile with tower position
    pos[Idx] = pos[0];
    // Remove tower
    pos[0] = 0;

    // If column was pending, player captures it
    if(cstate == ECstate::pend) {
        cstate = ECstate::capt;
        p->wonColumn(num);  // Record win
    }
}

// Print column state
ostream& Column::print(ostream& out) {
    // Print column number and state
    out << num << "\t" << cstate << "\t";

    // Iterate through each position in column
    for(int Idx = 1; Idx <= columnLength; Idx++) {
        out << "  ";  // Space before marker display
        bool empty = true;  // Track if position has any markers

        // Check if tower is at current position
        if(pos[0] == Idx) {
            out << "T";
            empty = false;
        } else
            out << "-";  // No tower, print placeholder

        // Check each colored tile at current position
        for(int Jdx = 1; Jdx < 5; Jdx++) {
            if(pos[Jdx] == Idx) {
                // Print letter for tile color:
                // O=orange, Y=yellow, G=green, B=blue
                switch(Jdx) {
                case 1: out << "O"; break;
                case 2: out << "Y"; break;
                case 3: out << "G"; break;
                case 4: out << "B"; break;
                }
                empty = false;
            } else
                out << "-";  // No tile, print placeholder
        }

        // Add space after non-empty positions
        if(!empty)
            out << "  ";
    }
    return out;
}