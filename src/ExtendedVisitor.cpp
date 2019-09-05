/*
 * ExtendedVisitor.cpp
 *
 *  Created on: Aug 29, 2019
 *      Author: linuxmotion
 */

#include "ExtendedVisitor.h"

ExtendedVisitor::ExtendedVisitor() {
	// TODO Auto-generated constructor stub

}

antlrcpp::Any ExtendedVisitor::visitCommand(
		CommandParser::CommandContext* context) {

	cout << "Visiting the initial command" << endl;
	cout << "command size: " << context->getText() << endl;
	return visitChildren(context);

	//return 1;
}
#include <string>

antlrcpp::Any ExtendedVisitor::visitPipe_sequence(
		CommandParser::Pipe_sequenceContext* context) {


	cout << "Visiting a pipe sequence" << endl;
	int size = context->children.size();
	// in the pipe seqeunce we have three parts
	// LHS = program1
	cout << context->children[0]->getText() << endl;
	// MID = pipe
	// RHS = pipe_sequence
	if(size == 3){


		cout << context->children[2]->getText() << endl;
		// We must first visit the next pipe sequence
		// which could be another pipe sequence
		// or a complex command

		antlrcpp::Any result = visitPipe_sequence(context->pipe_sequence());

		//We must the visit the left hand command
		//Once the RHS program is open we can then open the LHS
		// program and pipe the output from LHS to RHS

		return result;
	}else if(size == 1 ){
		return visitChildren(context);
	}

	return NULL;

}

antlrcpp::Any ExtendedVisitor::visitNew_program_sequence(
		CommandParser::New_program_sequenceContext* context) {


	cout << "Visiting a new program sequence" << endl;
	cout << "command size: " << context->children.size() << endl;
	visitChildren(context);
	return NULL;
}

antlrcpp::Any ExtendedVisitor::visitComplex_command(
		CommandParser::Complex_commandContext* context) {

	vector<string> arguments;

	// get the command name
	string command = context->command_name()->getText();
	//cout << context->children.size() << endl ;
	// here we need to fork and execute. but first we must gather our arguments
	log("command: " << command << " found")
	// the first child in the current context is actually the command name
	// so only loop to the children size -1
	for(unsigned int i = 0; i < (context->children.size()-1); i++){
		arguments.push_back(context->command_flags(i)->getText());
		log("argument #" << i << " " << context->command_flags(i)->getText() );
	}

	ProcessHelper helper;
	helper.ForkAndExecuteCommand(command, arguments,true);
	return NULL;
}

antlrcpp::Any ExtendedVisitor::visitSimple_command(
		CommandParser::Simple_commandContext* context) {

	// Here we would just fork and and execute our command

	cout << "Visiting a simple command" << endl;

	// We got the text of the command to execute
	string command = context->children[0]->getText() ;

	ProcessHelper helper;
	helper.ForkAndExecuteCommand(command, true);


	return NULL;
}

antlrcpp::Any ExtendedVisitor::visitCommand_name(
		CommandParser::Command_nameContext* context) {



	cout << "Visiting a command name" << endl;
	//cout << "command size: " << context->children.size() << endl;
	cout << "Name of command: " << context->getText() << endl;
	visitChildren(context);
	antlrcpp::Any text(context->getText());
	return text;
}

antlrcpp::Any ExtendedVisitor::visitCommand_flags(
		CommandParser::Command_flagsContext* context) {


	cout << "Visiting command flags" << endl;
	//cout << "command size: " << context->children.size() << endl;
	cout << context->getText() << endl;
	visitChildren(context);

	return context->getText();
}

ExtendedVisitor::~ExtendedVisitor() {
	// TODO Auto-generated destructor stub
}

