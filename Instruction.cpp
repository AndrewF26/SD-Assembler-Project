#include "stdafx.h"
#include "Instruction.h"

Instruction::Instruction() { };
Instruction::~Instruction() { };

/**/
/*
Instruction::ParseInstruction(string &a_line)

NAME

	Instruction::ParseInstruction(string &a_line)

SYNOPSIS

	InstructionType Instruction::ParseInstruction(string &a_line)
	a_line		--> the line in which we are parsing.

DESCRIPTION

	This function receives a line, and processes it to break the contents down into
	different variables that can be sorted.

RETURNS

	Returns the instruction type of the line.

AUTHOR

	Andrew Ferrand

DATE

	2:14pm 12/10/2022

*/
/**/
Instruction::InstructionType Instruction::ParseInstruction(string a_line)
{
	m_instruction = a_line;
	string a = "", b = "", c = "", d = "";

	// Getting rid of comment.
	int comment_loc;
	comment_loc = a_line.find(";");

	if (comment_loc != -1) 
	{
		a_line = a_line.substr(0, comment_loc);		// Now a_line is free of comments.
	}

	for (int i = 0; a_line[i]; i++) a_line[i] = tolower(a_line[i]);
	istringstream input(a_line);		
	input >> a >> b >> c >> d;

	if ((a_line == "") || (a_line == "\t") || (a_line == " ")) 
	{
		return ST_Comment;
	}

	if (a == "end") 
	{
		return ST_End;
	}

	if ((a_line[0] == ' ') || (a_line[0] == '\t') || (a_line[0] == NULL)) 
	{		
		// No label, a is opcode, b is operand.
		m_Label = "";
		m_OpCode = a;
		m_Operand = b;
	}

	// This means we have a label.
	else 
	{
		// a is label, b is opcode, c is operand.
		m_Label = a;
		m_OpCode = b;
		m_Operand = c;
	}

	// Making sure the operand string contains numeric value.
	m_IsNumericOperand = true;
	for (size_t i = 0; i < m_Operand.length(); i++)
	{
		if (!isdigit(m_Operand[i]))
			m_IsNumericOperand = false;
	}
	if (((m_Label != "") && ((m_OpCode == "ds") || (m_OpCode == "dc"))) || ((m_Label == "") && (m_OpCode == "org"))) 
	{
		return ST_MachineLanguage;
	}
	else 
	{
		return ST_AssemblerInstr;
	}
}

/**/
/*
Instruction::LocationNextInstruction(int a_loc)

NAME

	Instruction::LocationNextInstruction(int a_loc)

SYNOPSIS

	InstructionType Instruction::LocationNextInstruction(int a_loc)
	a_loc		--> the current location.

DESCRIPTION

	This function receives the current location and finds the location of the
	next line of code.

RETURNS

	Returns the location of the next instruction line.

AUTHOR

	Andrew Ferrand

DATE

	4:46pm 12/10/2022

*/
/**/
int Instruction::LocationNextInstruction(int a_loc) 
{
	// Determining the location according to the opcode.
	if (m_OpCode == "ds")
		a_loc = a_loc + atoi(m_Operand.c_str());
	else if (m_OpCode == "org") 
	{
		if (getIfNumOperand())
			a_loc = (atoi(m_Operand.c_str()));
		else
			a_loc = 0;
	}
	else
		a_loc++;

	return a_loc;
}
