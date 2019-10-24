#include <iostream>
#include <string>
#include <cstdlib>
#include <ctype.h>
#include "parser.h"
#include "code.h"
#include "SymbolTable.h"
using namespace std;

int main( int argc, char* argv[] ){
	
	Parser firstPass(argv[1]);
	Parser secondPass(argv[1]);
	SymbolTable stable;	

	//processing output file name
	string outFileName = argv[1];
	outFileName.erase(outFileName.length()-4,4);
	outFileName += ".hack";
	Code output(outFileName);


	int address_counter = 0;

	//first pass
	while( firstPass.hasMoreCommands() ){
		firstPass.advance();
		int line_size = firstPass.symbol().length();
		int cmdType = firstPass.commandType();
		
		if( cmdType < 2 && line_size > 0 ){
		//if A-cmd or C-cmd and not empty line
			address_counter++;
		}

		else if( cmdType == 2 && line_size > 0 ){
		//else if LABEL FOUND
			stable.addEntry(firstPass.symbol(),address_counter);
		}
	}

	//second pass
	while( secondPass.hasMoreCommands() ){
		secondPass.advance();
		int line_size = secondPass.symbol().length();
		int cmdType = secondPass.commandType();
		
		//A-commands
		if( cmdType == 0 ){
			//convert secondPass.symbol to an address through the table
			//if the entry exists, else it must be a number then just
			//call output.aCommand
			string a_command = secondPass.symbol();
			bool isPureNumeric = true;
			//testing for pure numeric a-commands
			for( int i = 0; i < a_command.length(); i++ ){
				if( !isdigit(a_command[i]) ){
					isPureNumeric = false;
					break;
				}	
			}
				
			if( stable.contains(a_command)){
			//LABEL CASE
				output.aCommand(to_string(stable.getAddress(a_command)));
			}

			else if( !stable.contains(a_command) && !isPureNumeric ){
			//VARIABLE CASE
				stable.addVariable(a_command);
				output.aCommand(to_string(stable.getAddress(a_command)));
			}

			else{
			//NUMBER CASE
				output.aCommand(a_command);
			}
		}
		
		//C-commands
		else if( cmdType == 1 && line_size > 0 ){
			output.cCommand(secondPass.returnCurrentLine());
			output.dest(secondPass.dest());
			output.comp(secondPass.comp());
			output.jump(secondPass.jump());
			output.writeToFile();
		}
	}

	return 0;
}
