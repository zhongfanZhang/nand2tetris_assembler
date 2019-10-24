#ifndef CODE_H
#define CODE_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

class Code{

	public:

		Code( std::string );
		void aCommand( std::string );
		void cCommand( std::string );
		void dest( std::string );
		void comp( std::string );
		void jump( std::string );
		void writeToFile();
		void printBin();
	
	private:

		std::string bin_command;
		std::ofstream ofile;

};

#endif
