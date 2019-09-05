/*
 * ProcessHelper.h
 *
 *  Created on: Aug 30, 2019
 *      Author: linuxmotion
 */

#ifndef PROCESSHELPER_H_
#define PROCESSHELPER_H_

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>

#include "ShellUtils.h"

using std::vector;

class ProcessHelper {
public:
	ProcessHelper();

	bool ForkAndExecuteSingleCommand(string command, bool wait);
	void ForkAndExecuteCommandArguments(string command, vector<string> cargs);
	virtual ~ProcessHelper();
	void ExecuteChildCommand(string);
private:

	bool ParentExecutionAfterFork(pid_t pid, bool should_wait);
};

#endif /* PROCESSHELPER_H_ */
