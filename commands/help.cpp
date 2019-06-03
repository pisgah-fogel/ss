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

#include "help.h"

#include "../config.h"
#include <iostream>
#include <vector>

void cmd::help (std::vector<std::string> &args) {
	if (args.size() == 1) { // no arguments
		std::cout<<"- Commands are:"<<std::endl;
		std::cout<<"set <pos> <val> | Set a cell value"<<std::endl;
		std::cout<<"get <pos> | Get a cell value"<<std::endl;
		std::cout<<"run <pos> | Compute a cell function"<<std::endl;
		std::cout<<"help [cmd] | Print help for command [cmd]"<<std::endl;
		std::cout<<"help | Print this"<<std::endl;
		std::cout<<"(q) quit | quit the program"<<std::endl;
		std::cout<<"exit | same as quit"<<std::endl;
		std::cout<<"- Positions are:"<<std::endl;
		std::cout<<"Example: A0 to Z9"<<std::endl;
		std::cout<<"You can use multiple character like: AA00 to ZZ99"<<std::endl;
		std::cout<<"- Cell's values are:"<<std::endl;
		std::cout<<"Function | Functions starting with '='"<<std::endl;
		std::cout<<"String | Anything (but can't be computed easily)"<<std::endl;
		std::cout<<"Integer | Integers"<<std::endl;
		std::cout<<"Float | Real numbers"<<std::endl;
	}
	else {
		// TODO: implement command specific help
		std::cout<<"Help for a given command is not yet implemented"<<std::endl;
	}
}
