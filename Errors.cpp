//
//      Implementation of the Error class.
//
#include "stdafx.h"
#include "Errors.h"


vector<string> Errors::m_ErrorMsgs;

/**/
/*
Errors::InitErrorReporting()

NAME

	Errors::InitErrorReporting()

SYNOPSIS

	void Errors::InitErrorReporting()

DESCRIPTION

	This function empties the vector m_ErrorMsgs at the beginning of the program.

RETURNS

	Nothing.

AUTHOR

	Andrew Ferrand

DATE

	12:05pm 11/27/2022

*/
/**/
void Errors::InitErrorReporting() 
{
	if (m_ErrorMsgs.empty())
		return;
	else 
	{
		m_ErrorMsgs.clear();
		return;
	}
}

/**/
/*
Errors::RecordError(string &a_emsg)

NAME

	Errors::RecordError(string &a_emsg)

SYNOPSIS

	void Errors::RecordError(string &a_emsg)
	a_emsg		--> The error message to record.

DESCRIPTION

	This function pushes the error message in a vector.

RETURNS

	Nothing.

AUTHOR

	Andrew Ferrand

DATE

	12:33pm 11/27/2022

*/
/**/
void Errors::RecordError(string& a_emsg) 
{
	// Pushing an error into the errors vector.
	m_ErrorMsgs.push_back(a_emsg);
}

/**/
/*
Errors::DisplayErrors()

NAME

	Errors::DisplayErrors()

SYNOPSIS

	void Errors::DisplayErrors()

DESCRIPTION

	This function outputs all the errors for each line based on the order 
	they were found.

RETURNS

	Nothing.

AUTHOR

	Andrew Ferrand

DATE

	1:09pm 11/27/2022

*/
/**/
void Errors::DisplayErrors() 
{
	// Prints all the errors that are in the errors vector.
	for (int i = 0; i < m_ErrorMsgs.size(); i++)
	{
		cout << "ERROR: " << m_ErrorMsgs[i] << endl;
	}

	// After printing the errors, popping them out of the vector.
	for (int i = 0; i < m_ErrorMsgs.size(); i++)
	{
		m_ErrorMsgs.pop_back();
	}
}