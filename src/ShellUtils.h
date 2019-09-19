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
#include <vector>

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
	bool ContinueRunningShell;

protected:

	int getInternalCommand(string command);
	static const int BUFFER_SIZE = 256;
	char mCurrentDir[BUFFER_SIZE];
	vector<string> INTERNAL_COMMANDS;
	string handleDotandTilde(const string commandToken, char cwd[]);
	string inline tildeExpansion();



	//void callCD(char* cwd, vector<string> tokens);
};

#endif /* SHELLUTILS_H_ */
