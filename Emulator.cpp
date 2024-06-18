//
//      Implementation of the Emulator class.
//
#include "stdafx.h"
#include "Emulator.h"

/**/
/*
Emulator::insertMemory(int a_location, int a_contents)

NAME

	Emulator::insertMemory(int a_location, int a_contents)

SYNOPSIS

	bool Emulator::insertMemory(int a_location, int a_contents)
	a_location		--> the location to insert into memory.
	a_contents		--> the contents to insert into memory.

DESCRIPTION

	This function receives and inserts the location and contents from
	translation to the memory.

RETURNS

	Returns true if contents added successfully. False otherwise.

AUTHOR

	Andrew Ferrand

DATE

	6:09pm 12/16/2022

*/
/**/
bool emulator::insertMemory(int a_location, long long a_contents)
{
	if (a_location < MEMSZ)
	{
		m_memory[a_location] = a_contents;
		return true;
	}
	else
	{
		return false;
	}
}

/**/
/*
Emulator::runProgram()

NAME

	Emulator::runProgram()

SYNOPSIS

	bool Emulator::runProgram()

DESCRIPTION

	This function runs the emulator which simulates the VC407.

RETURNS

	Returns true if ran successfully. False otherwise.

AUTHOR

	Andrew Ferrand

DATE

	12:20pm 12/18/2022

*/
/**/
bool emulator::runProgram()
{
	cout << "Results from emulating program:" << endl;
	int opCode, address, userInput;

	// Runs through memory.
	for (int i = 100; i < MEMSZ; i++)
	{

		// If memory is not empty, process its contents.
		if (m_memory[i] != 0)
		{
			address = m_memory[i] % 100000;		// Last 5 digits of contents which represent location.
			opCode = m_memory[i] / 100000;		// First 1 or 2 digits of contents represent OpCode.
			if (opCode == 1) 
			{ 
				accumulator += m_memory[address]; 
			}
			else if (opCode == 2) 
			{ 
				accumulator -= m_memory[address]; 
			}
			else if (opCode == 3) 
			{ 
				accumulator *= m_memory[address]; 
			}
			else if (opCode == 4) 
			{ 
				accumulator /= m_memory[address]; 
			}
			else if (opCode == 5) 
			{ 
				accumulator = m_memory[address]; 
			}
			else if (opCode == 6) 
			{ 
				m_memory[address] = accumulator; 
			}
			else if (opCode == 7)
			{
				cout << "? ";
				cin >> userInput;
				m_memory[address] = userInput;
			}
			else if (opCode == 8) 
			{ 
				cout << m_memory[address] << endl; 
			}
			else if (opCode == 9) 
			{ 
				i = address; 
			}
			else if (opCode == 10) 
			{ 
				if (accumulator < 0)
					i = address - 1; 
			}
			else if (opCode == 11) 
			{ 
				if (accumulator == 0)
					i = address - 1; 
			}
			else if (opCode == 12) 
			{ 
				if (accumulator > 0)
					i = address - 1; 
			}
			else if (opCode == 13) 
			{ return true; 
			}
			else 
			{ 
				cout << "Error: OpCode does not exist" << endl; 
			}

		}
	}
	return true;
}