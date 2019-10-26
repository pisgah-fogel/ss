#ifndef RUN_H
#define RUN_H

#include <iostream>
#include <string>
#include <vector>

enum ContexType
{
	None,
	EntryPoint,
	InBrackets, // ()
	InFunctionArgument, // ()
	InCurlyBrackets, // {}
	InInvertedCommas, // ""
	InSingleInvertedCommas, // ''
	InSquareBrackets, // []
	InBabyInvertedCommas // ``
};

// Structure to build a "Context Tree"
// Example: A(B(C() + D()) + E())
// A: parent=NULL child=B next=NULL previous=NULL
// B: parent=A child=C next=E previous=NULL
// C: parent=B child=NULL next="+" previous= NULL
// "+": parent=NULL child=NULL next=D previous=C // TODO: Should I use NULL parents ?
// D: parent=NULL child=NULL next=NULL previous="+"
// "+": parent=NULL child=NULL next=E previous="B"
// E: parent=NULL child=NULL next=NULL previous="+"
//
// A
// |
// v
// B ------------> + -----------> E
// |
// v
// C -> + -> D
typedef struct
{
	Contex *parent,
	Contex *child,
	Contex *next,
	Contex *previous,
	String str,
	ContexType type
} Context;

std::vector<Context*> sharedContexts;

Context* createContext(
	Contex *parent,
	Contex *child,
	Contex *next,
	Contex *previous,
	String str,
	ContexType type
	)
{
	Context *ptr = new Context{parent, child, next, previous, str, type};
	std::cout<<"Create context for \""<<str<<"\""<<std::endl;
	sharedContexts.push(ptr);
	return ptr;
}

void freeAllContexts()
{
	std::cout<<"We will delete "<<sharedContexts.size()<<" contexts"<<std::endl;
	for (auto it = sharedContexts.begin(); it != sharedContexts.end(); it++) {
		delete(*it);
	}
	sharedContexts.clear();
}

enum ConcatenationType
{
	None, // We are not concatening characters
	Int, // We are contatening 0-9 only
	ExInt, // 0-9 and x and b
	Float, // 0-9 and .
	String, // We are concatening something else (function, keyword or variable)
	Operator, // + - / ? ! ^ && || =
	Comparator, // < > <= >= == != /=
	VariableAccessor // % # $
};

std::string run(std::string str)
{
	if (str.at(0) != "=") {
		std::cout<<"This is not a function, it doesn't start with '='"<<std::endl;
		return str;
	}
	
	std::string concat = "";
	ConcatenationType concatType = None;
	Context *current = nullptr;
	for (char &c: str) {
		concat += c;
		if (c>='a' && c<='z' || c>='A' && c<='Z' || c == '_') {
		} else if (c == "=") {
			if (current == nullptr) {
				// Create EntryPoint
				current = createContext(nullptr, nullptr, nullptr, nullptr, concat, EntryPoint);
				concat.clear();
			} else {
				// Add a neighbor 
				Context *tmp = createContex(nullptr, nullptr, nullptr, nullptr, concat, None);
				tmp->previous = current;
				current->next = tmp;
				current = tmp;
				concat.clear();
			}
		} else if (c>='0' && c<='9') {
		} else {
			std::cout<<"Character '"<<c<<"' not expected"<<std::endl;
		}
	}
	std::string result;

	// TODO set result
	
	freeAllContexts();
	return result;
}

#endif // RUN_H
