/**
 * 
 * Define a grammar called Hello
 * 
 * 
 */
grammar Command;

// match any words followed by a command deliminator

command  : 
		| complex_command
		| pipe_sequence 
		| new_program_sequence
		;

pipe_sequence :  
			complex_command
		 |  complex_command PIPE  pipe_sequence
		;
		
		
new_program_sequence :
		   complex_command 
		|  new_program_sequence SEMICOLON command 
		;
		
complex_command :
		  simple_command
		| command_name command_flags+;
		
simple_command : 
		    command_name 
		; 
		


command_name: WORD;
command_flags: WORD;


// Matches any alpha numeric word as well as any word preceded
// by the - symbol i.e. flags arguments, and command names
WORD : '-'?[a-zA-Z0-9]+; 


// right now we will handle only three symbols

// Symbol to denote the end of command sequence
// allows another command to be ran after completion or failure
SEMICOLON : ';' ;

// used to denote the running of a task in the background
// or if used as && to denote the use of a conditional execution
AMPERSAND : '&' ; 

// used to denote the running of a task in the background
// or if used as || to denote the use of a conditional execution
PIPE : '|';


WS 
 : [ \t\r\n]+ -> skip // skip spaces, tabs, newlines
 ; 

