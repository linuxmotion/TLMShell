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
	do{

		cout << "~/ $ " ;
		in = "";
		getline(cin, in);
		ins << in;
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
		tree::ParseTree *tree = parser.command();
		visitor.visit(tree);

	}while(runShell);

	return 0;
}

Shell::~Shell() {
	// TODO Auto-generated destructor stub
}

