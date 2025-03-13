/*
* enums.hpp - Header file for game enumerations and color definitions
 * Author: Ryan Godburn & Arjun Aravind
 * Date: 1/31/25
 * Description: This header file defines the color and state
 *              enumeration used in the game and provides
 *              helper functions for output.
 */

#ifndef ENUMS_HPP
#define ENUMS_HPP

#pragma once

#include "tools.hpp"

// enum declarations
enum class ECcolor { white, orange, yellow, green, blue };
enum class ECstate { avail, pend, capt };

// array declarations
extern const string colorNames[];
extern const string stateNames[];

// Color output operator
inline ostream& operator<<(ostream& out, ECcolor color) {
    return out << colorNames[(int)color];
}

// State output operator
inline ostream& operator<<(ostream& out, ECstate state) {
    return out << stateNames[(int)state];
}

#endif