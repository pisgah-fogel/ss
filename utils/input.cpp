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

#include "input.h"

static struct termios mOld, mNew;

void initTermios(int echo) 
{
	tcgetattr(0, &mOld);
	mNew = mOld;
	mNew.c_lflag &= ~ICANON;
	if (echo) {
		mNew.c_lflag |= ECHO; // echo mode
	} else {
		mNew.c_lflag &= ~ECHO; // no echo mode
	}
	tcsetattr(0, TCSANOW, &mNew); // use the new config
}

void resetTermios(void) 
{
	  tcsetattr(0, TCSANOW, &mOld);
}

char getch_(int echo) 
{
	  char ch;
	    initTermios(echo);
	      ch = getchar();
	        resetTermios();
		  return ch;
}

char getche(void) 
{
	  return getch_(1);
}

char getch(void) 
{
	  return getch_(0);
}

std::string getLine()
{
	std::string input;
	char old1 = SS_CHAR_NONE;
	char old2 = SS_CHAR_NONE;
	char c = SS_CHAR_NONE;
	while (c != SS_CHAR_EOL) {
		old2 = old1;
		old1 = c;
		c = getch();
		if (old2 == SS_CHAR_ECH1 && old1 == SS_CHAR_ECH2) {
			switch (c) {
				case SS_CHAR_SPE_UP: // Up
					std::cout<<"\033[1A";
					break;
				case SS_CHAR_SPE_DOWN: // Down
					std::cout<<"\033[1B";
					break;
				case SS_CHAR_SPE_RIGHT: // Right
					std::cout<<"\033[1C";
					break;
				case SS_CHAR_SPE_LEFT: // Left
					std::cout<<"\033[1D";
					break;
				default:
					std::cout<<"special "<<c<<": "<<(unsigned int)c<<std::endl;
			}
		} else {
			switch (c) {
				case SS_CHAR_EOL:
					break;
				case SS_CHAR_ECH1: // echap 1
					break;
				case SS_CHAR_ECH2: // echap 2
					break;
				case SS_CHAR_DEL: // delete
					std::cout<<"\033[1D \033[1D";
					break;
				default:
					std::cout<<"! "<<c<<": "<<(unsigned int)c<<std::endl;
					input.push_back(c);
			}
		}
	}
	return input;
}
