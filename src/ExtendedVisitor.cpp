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

	log("Visiting the initial command");
	log("command size: " << context->children.size() );
	log("command name: " << context->getText() );
	//visit(context);
	return visitChildren(context);


}

antlrcpp::Any ExtendedVisitor::visitPipe_sequence(
		CommandParser::Pipe_sequenceContext* context) {

	log("Visiting a pipe sequence");
	int size = context->children.size();
	// in the pipe seqeunce we have three parts
	// LHS = program1
	cout << context->children[0]->getText() << endl;
	// MID = pipe
	// RHS = pipe_sequence
	if (size == 3) {

		cout << context->children[2]->getText() << endl;
		// We must first visit the next pipe sequence
		// which could be another pipe sequence
		// or a complex command

		antlrcpp::Any result = visitPipe_sequence(context->pipe_sequence());

		//We must the visit the left hand command
		//Once the RHS program is open we can then open the LHS
		// program and pipe the output from LHS to RHS

		return result;
	} else if (size == 1) {
		return visitChildren(context);
	}

	return EXIT_SUCCESS;

}

antlrcpp::Any ExtendedVisitor::visitNew_program_sequence(
		CommandParser::New_program_sequenceContext* context) {

	cout << "Visiting a new program sequence" << endl;
	cout << "command size: " << context->children.size() << endl;
	visitChildren(context);
	return EXIT_SUCCESS;
}


antlrcpp::Any ExtendedVisitor::visitComplex_command(
		CommandParser::Complex_commandContext* context) {

	log("Starting a complex command");
	vector<string> arguments;



	// check to see if we are a single command
	if (context->children.size() == 1) {
		// if we are just visit it
		visitChildren(context);
		return EXIT_SUCCESS;
	}

	// get the command name
	string command = context->command_name()->getText();

	log("command: " << command << " found")



	// here we need to fork and execute. but first we must gather our arguments

	// the first child in the current context is actually the command name
	// so only loop to the children size -1
	for (unsigned int i = 0; i < (context->children.size() - 1); i++) {
		arguments.push_back(context->command_flags(i)->getText());
		log("argument #" << i << " " << context->command_flags(i)->getText() );
	}

	// execute one of the internal command if it present
	if (Utilities.executeInternalCommand(command, arguments)  && (errno == 0))
		return EXIT_SUCCESS;
	else if(errno != 0){
		cout << command << ": " << strerror(errno) << endl;
		return EXIT_FAILURE;
	}


	ProcessHelper helper;
	helper.ForkAndExecuteCommand(command, arguments, true);

	return EXIT_SUCCESS;
}

antlrcpp::Any ExtendedVisitor::visitSimple_command(
		CommandParser::Simple_commandContext* context) {

	// Here we would just fork and and execute our command

	log("Visiting a simple command");

	// We got the text of the command to execute
	string command = context->command_name()->getText();

	// execute one of the internal command if it present
	errno = 0;
	if (Utilities.executeInternalCommand(command) && (errno == 0)  )
		return EXIT_SUCCESS;
	else if(errno != 0){
		cout << "cd: " << strerror(errno);
		return EXIT_FAILURE;
	}



	// if it is execute the internal command instead of forking

	// else fork and execute


	ProcessHelper helper;
	helper.ForkAndExecuteCommand(command, true);

	return EXIT_SUCCESS;
}

antlrcpp::Any ExtendedVisitor::visitCommand_name(
		CommandParser::Command_nameContext* context) {

	log( "Visiting a command name");
	//cout << "command size: " << context->children.size() << endl;
	log("Name of command: " << context->getText() );
	visitChildren(context);
	antlrcpp::Any text(context->getText());
	return text;
}

antlrcpp::Any ExtendedVisitor::visitCommand_flags(
		CommandParser::Command_flagsContext* context) {

	log("Visiting command flags");
	//cout << "command size: " << context->children.size() << endl;
	log(context->getText());
	visitChildren(context);

	return context->getText();
}

bool ExtendedVisitor::continueVisiting() {

	return Utilities.ContinueRunningShell;
}

ExtendedVisitor::~ExtendedVisitor() {
	// TODO Auto-generated destructor stub
}

