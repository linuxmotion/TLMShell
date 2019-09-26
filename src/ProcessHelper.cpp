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

/**
 * Executes the command in the child process.
 */
bool ProcessHelper::ParentExecutionAfterFork(pid_t pid, bool wait) {

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

	return true;
}


/**
 * Finishes execution of the parent process
 * after it has been forked.
 * Return true on success and exit on failure
 *
 */
bool ProcessHelper::ForkAndExecuteCommand(string command, vector<string> cargs, bool wait) {

	pid_t pid = fork();

	if(pid){


		log("Parent execution after fork started")

		ParentExecutionAfterFork(pid, wait);
		//i am in the parent process
	}else if(pid == 0){
		// i am in the child process
		ExecuteCommandArguments(command, cargs);

	}else{

		perror("An unhandled error has occurred");

		exit(EXIT_FAILURE);// and error accured
	}

return true;

}

void ProcessHelper::ExecuteCommandArguments(string command, vector<string> cargs) {


	log("Executing command " << command )
	unsigned int size = cargs.size();
	log("found " << size <<" arguments")
	// we need an c string array where the first element is the name
	// of the command and the last element is NULL
	char **args = new char*[size + 2];
	args[size+1] = 0; // Null the last argument

	// put all the arguments into the c string array
	for(unsigned int i = 0; i < size; i++){
			// copy the 0 to size-1 strings from our command arguments array
			// into the arguments array from 1 to size of our arguments list
			// copy all characters
			args[i+1]  = new char[25];
			cargs[i].push_back('\0'); // null terminate string
			cargs[i].copy(args[i+1], cargs[i].size(), 0);
	}



	char *buf = new char[256];
	command.push_back('\0'); // null terminate string
	command.copy(buf, command.size(), 0);
	//strcpy(buf,command.c_str());
	args[0] = buf;
	//args[1] = NULL;


	//const char *commandp = command.c_str(); // convert to c string
	int stat = execvp(args[0],args); // pass both to the exec service


	//if we reached here there was an error
	delete args;
	perror("Executing the command with the child process failed");
	exit(EXIT_FAILURE);
}

ProcessHelper::~ProcessHelper() {
	// TODO Auto-generated destructor stub
}

// Returns true in the parent thread if the child thread was
// created successfully, Exits in the child process
bool ProcessHelper::ForkAndExecuteCommand(string command, bool wait) {
	return ForkAndExecuteCommand(command, vector<string>(0), wait);
}
