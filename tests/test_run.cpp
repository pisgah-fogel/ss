#include "../commands/run.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

bool randomInt() {
	int output_int = 0;
	int input = rand();
	std::string output = run(std::to_string(input));

	try {
		output_int = std::stoi(output);
	} catch (...) { // can be std::invalid_argument or std::out_of_range
		std::cout<<"RandomInt failed"<<std::endl;
		std::cout<<"Return "<<output<<" instead of "<<input<<std::endl;
	}

	if (output_int != input) {
		std::cout<<"RandomInt failed"<<std::endl;
		std::cout<<"Input "<<input<<" | Ouput "<<output<<"Expected "<<input<<std::endl;
		return false;
	}
	return true;
}

// TODO: Add a seed command line parameter
int main(int argc, char **argv)
{
	unsigned int errors = 0;
	int seed = time(0);
	if (argc == 2) {
		try {
			int seed = std::stoi(argv[1])
		} catch (...) {
			std::cout<<argv[1]<<" is not a valid Seed: Using a time(0)"std::endl;
		}
	}	
	
	srand(seed);
	std::cout<<"Info: Seed="<<seed<<std::endl;

	if (!randomInt()) {
		errors++;
	}


	if (errors != 0) {
		std::cout<<"Test failed - "<<errors<<" errors"<<std::endl;
	} else {
		std::cout<<"Test passed"<<std::endl;
	}

	return 0;
}
