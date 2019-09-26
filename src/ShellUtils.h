/*
 * ShellUtils.h
 *
 *  Created on: Aug 30, 2019
 *      Author: linuxmotion
 */

#ifndef SHELLUTILS_H_
#define SHELLUTILS_H_
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <pwd.h>
#include <cerrno>

#include <sys/types.h>
#include <sys/wait.h>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;

// Comment this out to disable debuging
#define DEBUG

#ifdef DEBUG

#define log(String) \
		cout << __FILE__ << "::"<< __FUNCTION__ << "::"<< __LINE__ << " " << String << endl;
#else
#define log(String)
#endif



class ShellUtils {
public:
	ShellUtils();
	virtual ~ShellUtils();
	bool executeInternalCommand(string command);
	bool executeInternalCommand(string command, vector<string> arguments);
	bool ContinueRunningShell;
	string static getCWorkingDirectory();
	string static tildeExpansion();
protected:

	// Variables
	string CurrentDir;
	const static int BAILOUT = 5;
	const static int BUFFER_SIZE = 256;
	vector<string> INTERNAL_COMMANDS;

	//Functions
	int getInternalCommand(string command);
	string handleDotandTilde(const string commandToken, char cwd[]);

	string expandDotPath(string path);
	string expandDoubleDotPath(string path);
	bool callCD(string dir);


};

#endif /* SHELLUTILS_H_ */
