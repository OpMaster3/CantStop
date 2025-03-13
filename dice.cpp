/*
* dice.cpp - Implementation file for the Dice class.
 * Author: Ryan Godburn & Arjun Aravind
 * Date: 1/24/25
 * Description: This source file implements the methods in Dice.hpp.
 *              It includes the constructor, destructor, roll method, and print method
 *              for simulating and printing the dice values.
 */

#include "dice.hpp"

// Constructor
Dice::Dice(const int n) {
    nDice = n;           // Initialize number of dice
    dvals = new int[nDice]; // Dynamically allocate memory for dice values
}

// Destructor
Dice::~Dice() {
    delete[] dvals;  // Release allocated memory
}

// Roll dice
const int* Dice::roll() {
    for(int diceNum = 0; diceNum < nDice; diceNum++) {
        dvals[diceNum] = rand() % 6 + 1; // Generate random value between 1 and 6
    }
    return dvals; // Return array of dice values
}

// Print values
ostream& Dice::print(ostream& os) {
    for(int diceNum = 0; diceNum < nDice; diceNum++) {
        os << dvals[diceNum];    // Print each dice value
        if(diceNum < nDice - 1)  // Print space between values except after the last value
            os << " ";
    }
    return os; // Return ostream object
}