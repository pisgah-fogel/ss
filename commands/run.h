#ifndef RUN_H
#define RUN_H

#include <iostream>
#include <string>
#include <vector>

enum ContexType
{
	None,
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
	std::string result;
	std::cout<<"Not yet implemented"<<std::endl;
	
	std::string concat = "";
	ConcatenationType concatType = None;
	for (char &c: str) {
	}
	
	freeAllContexts();
	return result;
}

#endif // RUN_H
