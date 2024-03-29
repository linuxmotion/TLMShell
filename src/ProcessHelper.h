/*
 * ProcessHelper.h
 *
 *  Created on: Aug 30, 2019
 *      Author: linuxmotion
 */

#ifndef PROCESSHELPER_H_
#define PROCESSHELPER_H_

#include "ShellUtils.h"


class ProcessHelper {
public:
	ProcessHelper();

	bool ForkAndExecuteSingleCommand(string command, bool wait);
	bool ForkAndExecuteCommand(string command, bool wait);
	bool ForkAndExecuteCommand(string command, vector<string> cargs, bool wait) ;

	virtual ~ProcessHelper();
private:
	void ExecuteCommandArguments(string command, vector<string> cargs);
	bool ParentExecutionAfterFork(pid_t pid, bool should_wait);
};

#endif /* PROCESSHELPER_H_ */
