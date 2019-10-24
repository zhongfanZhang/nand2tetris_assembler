#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>
#include <iostream>
#include <string>

class SymbolTable{

	private:

		std::map<std::string, int> table;
		int variableCounter;
	
	public:

		SymbolTable();
		/* initialises predefined variables in constructor
		   SP,LCL,ARG,THIS,THAT,SCREEN,KBD & R0-15 and sets
		   initial variable counter to 16 */

		void addEntry( std::string, int );
		/* adds a label to the table, address acquired in the
		   first pass */

		void addVariable( std::string );
		/* adds a variable to the table, address starts at 16
		   and increments by 1 everytime a new variable is added */

		bool contains( std::string );
		/* determines whether a symbol has an entry using std::find */

		int getAddress( std::string );
		/* returns the address associated with a symbol */

};

#endif
