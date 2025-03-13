/*
* board.hpp - Header file for the Board class
 * Author: Ryan Godburn & Arjun Aravind
 * Date: 2/18/25
 * Description: This header defines the Board class which manages the
 *              game board and forms an interface between Game and Columns.
 */

#ifndef BOARD_HPP
#define BOARD_HPP

#pragma once

#include "tools.hpp"
#include "column.hpp"
#include "player.hpp"
#include <memory>

class Board {
private:
    // Tower tracking
    int nTowers;       // Number of towers in use (0-3)
    int towers[3] = {0, 0, 0};  // Which columns contain towers, initialized with constexpr

    // Array of Column pointers
    unique_ptr<Column> backBone[13];

    // Current player reference
    player* curPlayer;

public:
    Board();
    ~Board() = default;  // Smart pointers handle cleanup

    // Board operations
    void startTurn(player* p);
    bool move(int column);
    void stop();
    void bust();

    // Output
    ostream& print(ostream& out);
};

// Stream operator
inline ostream& operator<<(ostream& out, Board& board) {
    return board.print(out);
}

#endif