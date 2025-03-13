/*
* board.cpp - Implementation file for the Board class
 * Author: Ryan Godburn & Arjun Aravind
 * Date: 2/18/25
 * Description: This source file implements the Board class methods
 *              defined in board.hpp.
 */

#include "board.hpp"

// Constructor
Board::Board() : nTowers(0), curPlayer(nullptr) {
    // No need to initialize towers array (done in header)

    // Initialize backBone array
    // Elements 0 and 1 remain nullptr
    backBone[0] = nullptr;
    backBone[1] = nullptr;

    // Create Column objects for positions 2-12
    for(int Idx = 2; Idx <= 12; Idx++) {
        backBone[Idx] = std::make_unique<Column>(Idx);
    }
}

// Start a player's turn
void Board::startTurn(player* p) {
    curPlayer = p;
    nTowers = 0;

    // Reset tower tracking array
    for(int Idx = 0; Idx < 3; Idx++)
        towers[Idx] = 0;
}

// Handle move to a column
bool Board::move(int column) {
    // Column validation now handled by Game

    // Get column state
    Column& col = *backBone[column];
    ECstate state = col.state();

    // Cannot move to pending or captured columns
    if(state == ECstate::pend || state == ECstate::capt)
        return false;

    // Check if there's already a tower in this column
    bool hasTower = false;
    for(int Idx = 0; Idx < nTowers; Idx++) {
        if(towers[Idx] == column) {
            hasTower = true;
            break;
        }
    }

    if(hasTower) {
        // Tower exists in column, try to move it
        return col.move();
    } else { // No tower exists, try to place new one
        // Try to place new tower if we have less than 3
        if(nTowers >= 3)
            return false;

        // Start tower and track it if successful
        bool towerStarted = col.startTower(curPlayer);
        if(towerStarted) {
            towers[nTowers++] = column;
        }
        return towerStarted;
    }
}

// Stop turn and convert towers to tiles
void Board::stop() {
    // Process each tower
    for(int Idx = 0; Idx < nTowers; Idx++) {
        (*backBone[towers[Idx]]).stop(curPlayer);
    }
}

// Bust - remove all towers
void Board::bust() {
    // A player can't go bust if no towers
    if(nTowers == 0)
        return;

    // Handle bust in each column with a tower
    for(int Idx = 0; Idx < nTowers; Idx++) {
        (*backBone[towers[Idx]]).bust();
    }

    // Clear tower tracking
    nTowers = 0;
    for(int Idx = 0; Idx < 3; Idx++)
        towers[Idx] = 0;
}

// Print the board
ostream& Board::print(ostream& out) {
    // Header
    out << "==== BOARD STATUS ====\n";

    // Print each column (skip 0 and 1)
    for(int Idx = 2; Idx <= 12; Idx++) {
        out << *backBone[Idx] << "\n";
    }

    // Info about current towers
    out << "==== ACTIVE TOWERS: " << nTowers << " ====\n";
    for(int Idx = 0; Idx < nTowers; Idx++) {
        out << "Tower " << (Idx+1) << " in column " << towers[Idx] << "\n";
    }

    out << "====================\n";
    return out;
}