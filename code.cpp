#include "code.h"
using namespace std;

Code::Code( string ofile_name ){

	ofile.open( ofile_name.c_str() );
}

void Code::aCommand( string input ){
	bin_command = "0000000000000000\n";
	int i = 15;
	int a = atoi(input.c_str());
	while( a > 0 ){
		bin_command[i] =a%2 + 48;
		a /= 2;
		i--;
	}

	ofile << bin_command;
}

void Code::cCommand( string input ){
	bin_command = "1110000000000000\n";
}

void Code::dest( string input ){

	//10-12 of the binary string
	//M = last bit,	D = middle bit, A = first bit
	for( int i = 0; i < input.length(); i++ ){
		switch(input[i]){
			case 'A':
				bin_command[10] = '1';
				break;
			case 'D':
				bin_command[11] = '1';
				break;
			case 'M':
				bin_command[12] = '1';
				break;
		}
	}
}

void Code::comp( string input ){
	if( input.find("M") != string::npos ){
		bin_command[3] = '1';
	}

	//4-9 of the binary string
	if( input == "0" ){
		bin_command[4] = '1';
		bin_command[6] = '1';
		bin_command[8] = '1';
	}else if( input == "1" ){
		for( int i = 4; i < 10; i++ ){
			bin_command[i] = '1';
		}
	}else if( input == "-1" ){
		bin_command[4] = '1';
		bin_command[5] = '1';
		bin_command[6] = '1';
		bin_command[8] = '1';
	}else if( input == "D" ){
		bin_command[6] = '1';
		bin_command[7] = '1';
	}else if( input == "A" || input == "M" ){
		bin_command[4] = '1';
		bin_command[5] = '1';
	}else if( input == "!D" ){
		bin_command[6] = '1';
		bin_command[7] = '1';
		bin_command[9] = '1';
	}else if( input == "!A" || input == "!M" ){
		bin_command[4] = '1';
		bin_command[5] = '1';
		bin_command[9] = '1';
	}else if( input == "-D" ){
		for( int i = 6; i < 10; i++ ){
			bin_command[i] = '1';
		}	
	}else if( input == "-A" || input == "-M" ){
		bin_command[4] = '1';
		bin_command[5] = '1';
		bin_command[8] = '1';
		bin_command[9] = '1';
	}else if( input == "D+1" ){
		for( int i = 5; i < 10; i++ ){
			bin_command[i] = '1';
		}
	}else if( input == "A+1" || input == "M+1" ){
		bin_command[4] = '1';
		bin_command[5] = '1';
		bin_command[7] = '1';
		bin_command[8] = '1';
		bin_command[9] = '1';
	}else if( input == "D-1" ){
		bin_command[6] = '1';
		bin_command[7] = '1';
		bin_command[8] = '1';
	}else if( input == "A-1" || input == "M-1" ){
		bin_command[4] = '1';
		bin_command[5] = '1';
		bin_command[8] = '1';
	}else if( input == "D+A" || input == "D+M" ){
		bin_command[8] = '1';
	}else if( input == "D-A" || input == "D-M" ){
		bin_command[5] = '1';
		bin_command[8] = '1';
		bin_command[9] = '1';
	}else if( input == "A-D" || input == "M-D" ){
		bin_command[7] = '1';
		bin_command[8] = '1';
		bin_command[9] = '1';
	}else if( input == "D|A" || input == "D|M" ){
		bin_command[5] = '1';
		bin_command[7] = '1';
		bin_command[9] = '1';
	}
}

void Code::jump( string input ){
	//13,14,15 of the string
	if( input == "JGT" ){
		bin_command[15] = '1';
	}else if( input == "JEQ" ){
		bin_command[14] = '1';
	}else if( input == "JGE" ){
		bin_command[14] = '1';
		bin_command[15] = '1';
	}else if( input == "JLT" ){
		bin_command[13] = '1';
	}else if( input == "JNE" ){
		bin_command[13] = '1';
		bin_command[15] = '1';
	}else if( input == "JLE" ){
		bin_command[13] = '1';
		bin_command[14] = '1';
	}else if( input == "JMP" ){
		bin_command[13] = '1';
		bin_command[14] = '1';
		bin_command[15] = '1';
	}
}

void Code::writeToFile(){
	ofile << bin_command;
}

void Code::printBin(){
	cout << bin_command << endl;
}
