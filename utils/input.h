/*
 * This file is part of SS.
 * 
 * SS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 3.
 * 
 * SS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <stdio.h> // getch
#include <termios.h>

#define SS_CHAR_NONE '\0' // Not used value
#define SS_CHAR_EOL '\n' // End Of Line character
#define SS_CHAR_ECH1 27 // First echap character
#define SS_CHAR_ECH2 91 // Second echap character
#define SS_CHAR_DEL 127 // Delete character
#define SS_CHAR_SPE_UP 65 // Up special character
#define SS_CHAR_SPE_DOWN 66 // Down special character
#define SS_CHAR_SPE_RIGHT 67 // Right special character
#define SS_CHAR_SPE_LEFT 68 // Left special character

void initTermios(int echo);

void resetTermios(void);

char getch_(int echo);

char getche(void);

char getch(void);

std::string getLine();

#endif // INPUT_H
