/*
 * ShellUtils.cpp
 *
 *  Created on: Aug 30, 2019
 *      Author: linuxmotion
 */

#include "ShellUtils.h"

enum COMMANDS {
	CD, EXIT
};

ShellUtils::ShellUtils() {
	INTERNAL_COMMANDS.push_back("cd");
	INTERNAL_COMMANDS.push_back("exit");
	ContinueRunningShell = true;


}

/*
 * Takes a string as an argument, where the string
 * is the name of the command to find internally.
 * Returns the position of the command in the
 * internal commands list. Returns -1 if command
 * cannot be found in the list.
 */
int ShellUtils::getInternalCommand(string command) {

	for (unsigned int i = 0; i < INTERNAL_COMMANDS.size(); i++) {
		if (command.compare(INTERNAL_COMMANDS[i]) == 0)
			return i;
	}
	return -1;
}

/*
 * Takes a string of the name of the command to execute.
 * Executes the command internally if it is part of the
 * internal command list. returns true if a command
 * was executed and false if an internal command
 * was not found to execute.
 */
bool ShellUtils::executeInternalCommand(string command) {

	int com = getInternalCommand(command);

	switch (com) {

		case CD: {
			log("used internal cd command");
			break;
		};
		case EXIT: {

			log("used internal exit command");
			this->ContinueRunningShell = false;
			break;
		};
		default: {
			log("No command found, going to try and launch external command")
			return false;
		};

	};

	return true;
}

ShellUtils::~ShellUtils() {

}

