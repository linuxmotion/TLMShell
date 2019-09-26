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
 * was not found to execute. Sets errno if an error occurs
 * Set errno to 0 before function call and check on return to
 * see if and error has occured
 */
bool ShellUtils::executeInternalCommand(string command){
	vector<string> empty;
	return this->executeInternalCommand(command, empty);

}
/*
 * Takes a string of the name of the command to execute
 * and a vector of arguments
 * Executes the command internally if it is part of the
 * internal command list. returns true if a command
 * was executed and false if an internal command
 * was not found to execute. Sets errno if an error occurs
 * Set errno to 0 before function call and check on return to
 * see if and error has occured
 */
bool ShellUtils::executeInternalCommand(string command, vector<string> arguments) {

	int com = getInternalCommand(command);

	switch (com) {

		case CD: {
			log("used internal cd command");
			if(arguments.size() > 1){
				errno = E2BIG; // set earg list to long
				return false;
			}else if( arguments.size() == 1)
				return callCD(arguments[0]);
			else
				return callCD("");

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




/*
 * Return an expanded dot path
 *
 */
string ShellUtils::expandDotPath(string path){


	string expandDot;
	auto dir = this->getCWorkingDirectory();
	// add the cwd and chop off the dot
	expandDot = dir + path.substr(1);
	// add the cwd and chop off the dot
	return expandDot;
};
string ShellUtils::expandDoubleDotPath(string path){

	// string can be in the form
	// ../something
	// something/../stuff
	// somtheing/stuff/..
	// ../..~~~~



	// if path[0] and path[1] == '.'
	// then remove the last direct from CWD
	//


	string expandDoubleDot;
	// get the CWD
	auto dir = this->getCWorkingDirectory();
	// find the last / character for the path
	int dd = dir.find_first_of("..");
	int pos = dir.find_last_of('/');
	// we have a path with the last directory removed
	expandDoubleDot = dir.substr(0, pos-1);
	return expandDoubleDot;
};


string ShellUtils::handleDotandTilde(const string commandToken, char cwd[]) {
}


inline string ShellUtils::tildeExpansion() {


	char *pexpanded = getenv("HOME");

	// Get the value from the home variable
	if(pexpanded != NULL)
			return pexpanded;

	//if the home varaible is NULL then use the
	// uid to get the home dir
	return getpwuid(getuid())->pw_dir;


}

bool ShellUtils::callCD(string dir) {


	if(dir.compare("") == 0) // the empty string
		dir = tildeExpansion();
	else if( dir.compare("~") == 0) // the tilde string
		dir = tildeExpansion();

	dir += '\0';// add a null terminator

	if(chdir(dir.c_str()) == -1){
		log("chdir failed");

		return false;
	}

	return true;

}
/**
 * returns a string of the current working directory if successfull
 * or an empty string on failure
 *
 */
string ShellUtils::getCWorkingDirectory() {


	// allocate buffer
	char *cwdp = new char[BUFFER_SIZE];
	// get the diretory
	getcwd(cwdp, BUFFER_SIZE);

	// if pointer is null check for ERANGE
	if(cwdp == NULL){
		unsigned int loopc = 0;
		unsigned int bufs = 0;
		// if erange is set and we haven't bailed out
		while((errno == ERANGE) && (loopc < BAILOUT)){
			delete cwdp;// delete the old pointer
			cwdp = 0;
			bufs = BUFFER_SIZE * (loopc+1);// inncrease buffer
			cwdp = new char[bufs];
			loopc++;
			getcwd(cwdp,bufs);//try again
			// if getcwd fails errno is set to ERANGE again
			if(cwdp != NULL)// check for a vaild string
				break;
		}

		// check one last time to see if the pointer is valid
		if(cwdp == NULL)
			return ""; // if it was we could not allocate a big
		// enough space or another error occured
	}

	return cwdp; // the pointer is valid, covert to string

}


