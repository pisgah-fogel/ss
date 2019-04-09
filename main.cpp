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

#include <iostream>
#include <vector>
#include <map>

#include <stdlib.h> // strtoul

#include "config.h"

#ifdef CUSTOM
#include "input.h"
#endif

std::vector<std::string> splitCmd(std::string str)
{
	std::vector<std::string> splitted;
	bool escapeNext = false;
	bool inStr = false;
	std::string current;
	for(std::string::iterator it = str.begin(); it != str.end(); it++) {
		if (inStr) {
			if (!escapeNext && *it == '"') {
				inStr = false;
				splitted.push_back(current);
				current.clear();
			}
			else
				current.push_back(*it);
		} else {
			if (!escapeNext && *it == '"')
				inStr = true;
			else if (*it == ' ' || *it == '\t') {
				if (current.size() != 0) {
					splitted.push_back(current);
					current.clear();
				}
			}
			else
				current.push_back(*it);
		}
		escapeNext = (*it == '\\');
	}
	if (current.size() != 0) {
		splitted.push_back(current);
	}

#ifdef DEBUG
	for (std::vector<std::string>::iterator it = splitted.begin(); it != splitted.end(); it++)
		std::cout<<" ["<<*it<<"] ";
	std::cout<<std::endl;
#endif

	return splitted;
}

namespace ss {
	typedef std::pair<unsigned long int, std::string> position;
	typedef std::pair<std::string, std::string> cell;
}

bool isValidChar(char c)
{
	return (c >= 'A' && c <= 'Z');
}

bool isValidPosition(std::string str)
{
	std::string::iterator it = str.begin();
	while(it != str.end()){
		if (*it < 'A' || *it > 'Z')
			break; // bad format
		it++;
	}
	while(it != str.end()){
		if (*it < '1' || *it > '9')
			return false; // bad format
		it++;
	}

	return true;
}

ss::position parsePosition(std::string str)
{
	std::string lign, col;
	ss::position pos;
	std::string::iterator it = str.begin();
	while(it != str.end()){
		if (*it < 'A' || *it > 'Z')
			break; // bad format
		else
			col.push_back(*it);
		it++;
	}
	while(it != str.end()){
		if (*it < '1' || *it > '9') {
			std::cout<<"Error: bad position format, this is a critical warning"<<std::endl;
			return ss::position(0, ""); // bad format
		}
		else
			lign.push_back(*it);
		it++;
	}
	pos = ss::position(strtoul(lign.c_str(), NULL, 10), col);

	return pos;
}

std::string computeFunction(std::string str)
{
	std::string result;
	return result;
}

int main (int argc, char** argv)
{
	std::map<ss::position, ss::cell> mMap; // lignes and columns (alphabetics)
	bool quit = false;
	std::string cmd;

	std::cout<<"Welcome to GNU no-gui speadsheet software !"<<std::endl;

	while (quit == false)
	{
		std::cout<<"$ ";
#ifdef CUSTOM
		cmd = getLine();
#else
		std::getline(std::cin, cmd);
#endif
		if (cmd == "quit" || cmd == "exit" || cmd == "q") {
			quit = true;
		} else {
			std::vector<std::string> splitted = splitCmd(cmd);
			if (splitted.size() > 0 && splitted[0] == "set") {
				if (splitted.size() < 3)
					std::cout<<"Not enough arguments for set"<<std::endl;
				else if (splitted.size() > 3)
					std::cout<<"Too many arguments for set"<<std::endl;
				else {
					if (isValidPosition(splitted[1])) {
						ss::position pos = parsePosition(splitted[1]);
						if (mMap.find(pos) != mMap.end())
							std::cout<<"Cell remplaced"<<std::endl;
						else
							std::cout<<"Cell created"<<std::endl;
						if (splitted[2][0] == '=')
							mMap[pos] = ss::cell("Function", splitted[2]);
						else
							mMap[pos] = ss::cell("String", splitted[2]);
					} else
						std::cout<<"Bad position "<<splitted[1]<<std::endl;
				}
			}
			else if (splitted.size() > 0 && splitted[0] == "get") {
				if (splitted.size() == 1)
					std::cout<<"Not enough arguments for get"<<std::endl;
				else if (splitted.size() > 2)
					std::cout<<"Too many arguments for get"<<std::endl;
				else {
					if (isValidPosition(splitted[1])) {
						ss::position pos = parsePosition(splitted[1]);
						if (mMap.find(pos) != mMap.end())
							std::cout<<"["<<splitted[1]<<"] "<<mMap[pos].first<<" - "<<mMap[pos].second<<std::endl;
						else
							std::cout<<"No cell "<<splitted[1]<<" found"<<std::endl;
					} else
						std::cout<<"Bad position "<<splitted[1]<<std::endl;
				}
			}
			else if (splitted.size() > 0 && splitted[0] == "run") {
				if (splitted.size() == 1)
					std::cout<<"Not enough arguments for run"<<std::endl;
				else if (splitted.size() > 2)
					std::cout<<"Too many arguments for run"<<std::endl;
				else {
					if (isValidPosition(splitted[1])) {
						ss::position pos = parsePosition(splitted[1]);
						if (mMap.find(pos) != mMap.end()) {
							std::string type = mMap[pos].first;
							if (type == "Function")
								std::cout<<computeFunction(mMap[pos].second)<<std::endl;
							else if (type == "String")
								std::cout<<"\""<<mMap[pos].second<<"\""<<std::endl;
							else if (type == "Integer")
								std::cout<<"Int: "<<mMap[pos].second<<std::endl;
							else if (type == "Float")
								std::cout<<"Float: "<<mMap[pos].second<<std::endl;
							else
								std::cout<<"[Unknown]: "<<mMap[pos].second<<std::endl;
						}
						else
							std::cout<<"No cell "<<splitted[1]<<" found"<<std::endl;
					} else
						std::cout<<"Bad position "<<splitted[1]<<std::endl;
				}
			}
			else {
				std::cout<<"Command error"<<std::endl;
			}
		}
	}

	std::cout<<"See you soon"<<std::endl;
	std::cout<<"YARPA foundation wish you a fantastic evenning"<<std::endl;

	return 0;
}
