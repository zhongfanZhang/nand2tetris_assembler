#include "SymbolTable.h"
using namespace std;

SymbolTable::SymbolTable(){
	
	//initialise some predefined symbols
	table["SP"] = 0;
	table["LCL"] = 1;
	table["ARG"] = 2;
	table["THIS"] = 3;
	table["THAT"] = 4;
	table["SCREEN"] = 16384;
	table["KBD"] = 24576;
	for( int i = 0; i <= 15; i++ ){
		string reg = "R" + to_string(i);
		table[reg] = i;
	}

	//set initial variableCounter 16=0
	variableCounter = 16;

}

void SymbolTable::addEntry( string symbol, int addr ){
	table[symbol] = addr;
}

bool SymbolTable::contains( string symbol ){
	map<string,int>::iterator it;
	it = table.find(symbol);
	if( it != table.end() ){
		return true;
	}else{
		return false;
	}
}

int SymbolTable::getAddress( string symbol ){
	return table[symbol];
}

void SymbolTable::addVariable( string symbol ){
	//variables start at address 16, add one to the table
	//and increment variable count by 1
		table[symbol] = variableCounter;
		variableCounter++;
}

