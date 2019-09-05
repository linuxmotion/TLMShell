/*
 * TLMShell.cpp
 *
 *  Created on: Sep 5, 2019
 *      Author: linuxmotion
 */




//============================================================================
// Name        : TestProject.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "antlr4-runtime.h"
#include "CommandLexer.h"
#include "CommandParser.h"
//#include "ExtendedCommandListener.h"
#include "ExtendedVisitor.h"

using namespace std;
using namespace antlrcpp;
using namespace antlr4;

int main() {
	cout << "Enter a single command with no arguments" << endl; // prints !!!Hello World!!!

	string in = "";
	getline(cin, in);
	std::stringstream ins(in);
	// Create the input stream.
	//ins.open(args[1] );
	ANTLRInputStream input(ins);
	// Create a lexer which scans the input stream
	// to create a token stream.
	CommandLexer lexer(&input);
	//ExtendedCommandListener listener;
	ExtendedVisitor visitor;

	CommonTokenStream tokens(&lexer);

	// Print the token stream.
	cout << "Tokens:" << endl;
	tokens.fill();
	for (Token *token : tokens.getTokens()) {
		std::cout << token->toString() << std::endl;
	}
	// Create a parser which parses the token stream
	// to create a parse tree.
	CommandParser parser(&tokens);
	tree::ParseTreeWalker walker;
	tree::ParseTree *tree = parser.command();
	visitor.visit(tree);
	//walker.walk(&visitor, tree);
	//cout << endl << tree->getText() << endl;

	// Print the parse tree in Lisp format.
	cout << endl << "Parse tree (Lisp format):" << endl;
	std::cout << tree->toStringTree(&parser) << endl;
	return 0;

}
