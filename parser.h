#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>	//for std::remove

class Parser{

	private:

		std::string current_command;
		std::ifstream file;
		
	public:
		
		Parser(std::string);
		/* constructor opens the target file */

		bool hasMoreCommands();
		/* checks for end of file, returns true if eof() */

		void advance();
		/* continuously grabs the next line until the current line
		   is not entirely commented or end of file, this function	
		   also erases whitespace and inline comments from the current
		   line */

		int commandType();
		/* returns 0 if A-cmd, 1 if C-cmd and 2 if L-cmd, This function
		   also removes the brackets from L-cmds and "@" symbols from
		   A-cmds */

		std::string symbol();
		/* creates an alphanumeric string from the current_command
		   string and returns it */

		std::string dest();
		/* extracts the dest part of the C-cmd by finding the position
		   of the "=" symbol and grabs everythng to the left of it 
		   end of function returns the dest cmd as a string */

		std::string comp();
		/* extracts the comp part of the c-cmd by finding the position
		   of the "=" and ";" symbols end of function returns the cmp
		   cmd as a string */

		std::string jump();
		/* extracts the jmp part of c-cmds by finding the position of 
		   ";" symbols end of function returns the jmp cmd as a string */




		//=======================================debugging functions===================================================
		void printCurrentLine();
		std::string returnCurrentLine();

};


#endif
