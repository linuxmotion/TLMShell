/*
 * Shell.h
 *
 *  Created on: Sep 5, 2019
 *      Author: linuxmotion
 */

#ifndef SHELL_H_
#define SHELL_H_

#include "antlr4-runtime.h"
#include "CommandLexer.h"
#include "CommandParser.h"
//#include "ExtendedCommandListener.h"
#include "ExtendedVisitor.h"

using namespace std;
using namespace antlrcpp;
using namespace antlr4;


class Shell {
public:
	Shell();
	int StartShell();
	virtual ~Shell();
};

#endif /* SHELL_H_ */
