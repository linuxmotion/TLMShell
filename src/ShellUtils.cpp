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

	// TODO Auto-generated constructor stub

}

bool ShellUtils::isInternalCommand(string command) {

	for (unsigned int i = 0; i < INTERNAL_COMMANDS.size(); i++) {
		if (command.compare(INTERNAL_COMMANDS[i]) == 0)
			return true;
	}
	return false;
}

void ShellUtils::executeInternalCommand(string command) {

	int pos = -1;
	for (unsigned int i = 0; i < INTERNAL_COMMANDS.size(); i++) {
		if (command == INTERNAL_COMMANDS[i]) {
			pos = i;
			break;
		}
	}

	switch (pos) {

		case CD: {
			log("used internal cd command");
			break;
		}
		;
		case EXIT: {

			log("used internal exit command");
			this->ContinueRunningShell = false;
			break;
		}
		default: {
			return;
		}
		;

	};

	return;
}

ShellUtils::~ShellUtils() {
	// TODO Auto-generated destructor stub
}

