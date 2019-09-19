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

int ShellUtils::getInternalCommand(string command) {

	for (unsigned int i = 0; i < INTERNAL_COMMANDS.size(); i++) {
		if (command.compare(INTERNAL_COMMANDS[i]) == 0)
			return i;
	}
	return -1;
}

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
	// TODO Auto-generated destructor stub
}

