/*
* game.hpp - Header file for the Game class
 * Author: Ryan Godburn & Arjun Aravind
 * Date: 2/27/25
 * Description: This header defines the Game class which acts as the
 *              controller for the Can't Stop application.
 */

#ifndef GAME_HPP
#define GAME_HPP

#pragma once

#include "dice.hpp"
#include "player.hpp"
#include "board.hpp"
#include <memory>

class Game {
private:
    unique_ptr<Dice> dice;    // Set of 4 dice
    Board board;              // Game board
    unique_ptr<player> curPlayer; // Current player

    // Function to get player data
    player getNewPlayer();

public:
    Game();
    ~Game() = default;  // Smart pointers handle cleanup

    // Game turn function - modified to not require a player parameter
    void oneTurn();
};

#endif