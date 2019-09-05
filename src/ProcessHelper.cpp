/*
 * ProcessHelper.cpp
 *
 *  Created on: Aug 30, 2019
 *      Author: linuxmotion
 */

#include "ProcessHelper.h"


ProcessHelper::ProcessHelper() {
	// TODO Auto-generated constructor stub

}


void ProcessHelper::ExecuteChildCommand(string command) {
	// i am in the child process

	vector<string> cargs(0);
	this->ForkAndExecuteCommandArguments(command, cargs);
}

bool ProcessHelper::ParentExecutionAfterFork(pid_t pid, bool wait) {
	;
	/**
	 * if somewhere there is a &
	 * ie. command -flags &
	 * the the parent should not wait on the child
	 *
	 */
	//bool wait = true;
	log("Parent execution after fork started");

	if (wait) {
		log("Waiting on child process");
		int status;
		// wait for child to exit
		int pid_stat = waitpid(pid, &status, 0);
		//(pid, &status, 0);
		if (pid_stat < 0) {
			log("An error occured while waiting for the child process");
			perror(
					"An error occured while waiting for the child process");
			//return false;
		}
		if (WIFEXITED(status)) {
			log("Child exit status = " << WEXITSTATUS(status))
		}
	} else {
		log("Not waiting on child execution")

	} log("Parent execution after fork finished successfully");

	//return true;
}

/**
 * Finishes execution of the parent process
 * after it has been forked. If Tokes contains
 * an & the the parent process will not wait.
 * Return true on success and false on failure
 *
 */
bool ProcessHelper::ForkAndExecuteSingleCommand(string command, bool wait) {

	pid_t pid = fork();

	if(pid){


		log("Parent execution after fork started")

		ParentExecutionAfterFork(pid, wait);
		//i am in the parent process
	}
	else if(pid == 0){
		// i am in the child process
		ExecuteChildCommand(command);
	}else{

		perror("An unhandled error has occurred");

		exit(EXIT_FAILURE);// and error accured
	}











}

void ProcessHelper::ForkAndExecuteCommandArguments(std::string command, vector<string> cargs) {


	int size = cargs.size();
	// we need an c string array where the first element is the name
	// of the command
	char **args = new char*[size + 1];

	// put all the arguments into the c string array
	for(int i = 0; i < size; i++){
			// copy the 0 to size-1 strings from our command arguments array
			// into the arguments array from 1 to size of our arguments list
			// copy all characters
			cargs[i].copy(args[i+1], cargs[i].size(), 0);
	}


	//char **args = new char*[2];
	//command += "\0"; // add on a null terminator

	char *buf = new char[256];
	command.copy(buf, command.size(), 0);
	//strcpy(buf,command.c_str());
	args[1] = buf;
	args[1] = NULL;


	const char *commandp = command.c_str(); // convert to c string
	int status = execvp(commandp,args); // pass both to the exec service
	//if we reached here there was an error
	delete args;
	exit(EXIT_FAILURE);
}

ProcessHelper::~ProcessHelper() {
	// TODO Auto-generated destructor stub
}

