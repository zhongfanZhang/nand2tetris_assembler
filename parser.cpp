#include "parser.h"
using namespace std;

Parser::Parser( string filename ){
	file.open(filename.c_str());
}

bool Parser::hasMoreCommands(){
	if(file.eof()){
		return false;
	}else{
		return true;
	}
}

void Parser::advance(){
	while( !file.eof() ){
	//skip line comments
		getline(file,current_command);
		if( current_command[0] != '/' && current_command[1] != '/' ){
			//erase whitespace
			current_command.erase(remove(current_command.begin(),current_command.end(),' '),current_command.end());
			//remove inline comments
			size_t cpos = current_command.find("//");
			if( cpos != string::npos ){
				current_command.erase(cpos, current_command.length() - cpos - 1); 
			}
			break;
		}	
	}
}

int Parser::commandType(){

	//returns -1 if blank
	if( current_command == "\0" ){
		return -1;
	}

	//returns 0 if A_command
	//returns 1 if C_command
	//returns 2 if L_command
	if( current_command[0] == '@' ){
		//erase the @
		current_command.erase(0,1);
		return 0;
	}else if( current_command[0] == '(' ){
		//erase both brackets
		current_command.erase(0,1);
		int bpos = current_command.find(")");
		current_command.erase(bpos,1);
		return 2;
	}else{
		return 1;
	}

}

string Parser::symbol(){
	string out;
	for( int i = 0; i < current_command.length(); i++ ){
		if( isalnum(current_command[i]) ){
			out += current_command[i];
		}
	}

	return out;
}

string Parser::dest(){
	//dest cmds are always to the left of the = sign
	int pos = current_command.find("=");
	string out;
	if( pos > 0 ){
		out = current_command.substr(0,pos);
	}

	return out;
}

string Parser::comp(){
	int pos = current_command.find("=");
	int pos2 = current_command.find(";");
	string out;
	if( pos > 0 && pos2 > 0 ){
	//if both "=" and ";" are in the command line
		out = current_command.substr(pos+1,pos2-pos+1);	
	}else if( pos2 > 0 && pos < 0 ){
	//if only ";" is in the command line
		out = current_command.substr(0,pos2);
	}else if( pos > 0 && pos2 < 0 ){
	//if only "=" is in the command line
		out = current_command.substr(pos+1,current_command.length()-pos-2);
	}
	return out;
}

string Parser::jump(){
	//jmp cmds are always 3 characters long
	int pos = current_command.find(";");
	string out;
	if( pos > 0 ){
		out = current_command.substr(pos+1,3);
	}
	return out;
}



//================================debugging functions==================================================
void Parser::printCurrentLine(){
	cout << current_command << endl;
}

string Parser::returnCurrentLine(){
	return current_command;
}
