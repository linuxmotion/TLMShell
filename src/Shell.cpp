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


	int runShell = true;
	string in = "";
	std::stringstream ins(in);
	ANTLRInputStream input(ins);
	CommandLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	CommandParser parser(&tokens);
	ExtendedVisitor visitor;

	do{

		cout << "~/ $ " ;
		in = "";
		ins.clear();
		getline(cin, in);
		ins << in;
		// Create the input stream.
		//ins.open(args[1] );
		input.load(ins);
		// Create a lexer which scans the input stream
		// to create a token stream.
		lexer.setInputStream(&input);
		tokens.setTokenSource(&lexer);
		// Create a parser which parses the token stream
		// to create a parse tree.
		parser.setTokenStream(&tokens);
		tree::ParseTree *tree = parser.command();
		visitor.visit(tree);

		//if(visitor.visit(tree).equals(-1))
			//runShell = false;

	}while(visitor.continueVisiting());

	return 0;
}

Shell::~Shell() {
	// TODO Auto-generated destructor stub
}

