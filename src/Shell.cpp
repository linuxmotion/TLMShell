/*
 * Shell.cpp
 *
 *  Created on: Sep 5, 2019
 *      Author: linuxmotion
 */

#include "Shell.h"

Shell::Shell() {
	// TODO Auto-generated constructor stub

}

int Shell::StartShell() {


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


	// Create a parser which parses the token stream
	// to create a parse tree.
	CommandParser parser(&tokens);
	tree::ParseTreeWalker walker;
	tree::ParseTree *tree = parser.command();
	visitor.visit(tree);
	//walker.walk(&visitor, tree);
	//cout << endl << tree->getText() << endl;

	// Print the parse tree in Lisp format.
	//cout << endl << "Parse tree (Lisp format):" << endl;
	//std::cout << tree->toStringTree(&parser) << endl;


}

Shell::~Shell() {
	// TODO Auto-generated destructor stub
}

