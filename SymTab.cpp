//
//		Implementation of the symbol table class.  This is the format I want for commenting functions.
//
#include "stdafx.h"
#include "SymTab.h"

/*
NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( const string &a_symbol, int a_loc );
    	a_symbol	-> The name of the symbol to be added to the symbol table.
    	a_loc		-> the location to be associated with the symbol.

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc"
    in the symbol table.

*/
void SymbolTable::AddSymbol(const string &a_symbol, int a_loc)
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st = m_symbolTable.find(a_symbol);
    if (st != m_symbolTable.end()) 
    {
        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}

/**/
/*
SymbolTable::DisplaySymbolTable()

NAME

	SymbolTable::DisplaySymbolTable()

SYNOPSIS

	void SymbolTable::DisplaySymbolTable()

DESCRIPTION

	This functions displays the symbol table on the screen.

RETURNS

	Nothing.

AUTHOR

	Andrew Ferrand

DATE

	12:15pm 12/06/2022

*/
/**/
void SymbolTable::DisplaySymbolTable() 
{
	map<string, int>::iterator st;
	st = m_symbolTable.begin();
	int i = 0;

	// First line of table.
	cout << "Symbol#\tSymbol\tLocation" << endl;

	// Going through the symbol table and printing its contents line by line
	while (st != m_symbolTable.end()) 
	{
		cout << i << '\t' << st->first
			<< '\t' << st->second << '\n';
		st++;
		i++;
	}
	cout << endl;
	cout << "________________________________________________________" << endl;
}

/**/
/*
SymbolTable::LookupSymbol(string & a_symbol, int & a_loc)

NAME

	SymbolTable::LookupSymbol(string & a_symbol, int & a_loc)

SYNOPSIS

	bool SymbolTable::LookupSymbol(string & a_symbol, int & a_loc)
	a_symbol		--> the symbol to look up.
	a_loc			--> its corresponding location.

DESCRIPTION

	This functions attempts to search for a pair of symbols

RETURNS

	Returns true if pair is found, false otherwise.

AUTHOR

	Andrew Ferrand

DATE

	12:50pm 12/06/2022

*/
/**/

bool SymbolTable::LookupSymbol(const string & a_symbol, int& a_loc)
{

	// If symbol was found return true, otherwise false.
	if (m_symbolTable.count(a_symbol) != 0)
	{
		return true;
	}
	else return false;
}

/**/
/*
SymbolTable::findLabelLoc(string &a_symbol)

NAME

	SymbolTable::findLabelLoc(string &a_symbol)

SYNOPSIS

	void SymbolTable::DisplaySymbolTable()
	a_symbol		--> Symbol to look up in the table.

DESCRIPTION

	This function finds the location corresponding to a given symbol.

RETURNS

	Returns the location of the symbol if found, else returns -1.

AUTHOR

	Andrew Ferrand

DATE

	1:40pm 12/09/2022

*/
/**/
int SymbolTable::findLabelLoc(string& a_symbol) 
{
	map<string, int>::iterator st;

	// If a symbol was found, return its corresponding location.
	if (m_symbolTable.count(a_symbol))
	{
		st = m_symbolTable.find(a_symbol);
		return st->second;
	}
	else
		return -1;
}