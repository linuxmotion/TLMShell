/*
 * ExtendedVisitor.h
 *
 *  Created on: Aug 29, 2019
 *      Author: linuxmotion
 */

#ifndef EXTENDEDVISITOR_H_
#define EXTENDEDVISITOR_H_

#include <CommandVisitor.h>
#include <antlr4-runtime.h>

#include "ProcessHelper.h"


class ExtendedVisitor: public CommandVisitor {
public:
	ExtendedVisitor();

	/**
	 * Visit parse trees produced by CommandParser.
	 */
	virtual antlrcpp::Any visitCommand(CommandParser::CommandContext *context);

	virtual antlrcpp::Any visitPipe_sequence(CommandParser::Pipe_sequenceContext *context);

	virtual antlrcpp::Any visitNew_program_sequence(CommandParser::New_program_sequenceContext *context);

	virtual antlrcpp::Any visitComplex_command(CommandParser::Complex_commandContext *context);

	virtual antlrcpp::Any visitSimple_command(CommandParser::Simple_commandContext *context);

	virtual antlrcpp::Any visitCommand_name(CommandParser::Command_nameContext *context);

	virtual antlrcpp::Any visitCommand_flags(CommandParser::Command_flagsContext *context);

	virtual bool continueVisiting();

	virtual ~ExtendedVisitor();

private:
	ShellUtils Utilities;

};

#endif /* EXTENDEDVISITOR_H_ */
