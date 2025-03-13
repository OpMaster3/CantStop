/*
* dice.hpp - Header file for the Dice class.
 * Author: Ryan Godburn & Arjun Aravind
 * Date: 1/24/25
 * The class simulates a set of dice. It has methods for rolling
 * the dice and printing their values.
 */

#ifndef DICE_HPP
#define DICE_HPP

#pragma once

#include "tools.hpp"

class Dice {
private:
    int nDice;     // Number of dice
    int* dvals;    // Pointer to dynamically allocate array holding dice values
public:
    Dice(int n = 1);
    ~Dice();
    ostream& print(ostream&);
    const int* roll();
};

#endif

// Overloaded stream insertion operator to print the Dice object
inline ostream& operator<<(ostream& os, Dice& d) {
    return d.print(os);
}

