//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"
#include "SymTab.h"


// Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
// See main program.  
Assembler::Assembler(int argc, char *argv[])
: m_facc(argc, argv)
{
    // Nothing else to do here at this point.
}  
// Destructor currently does nothing.  You might need to add something as you develope this project.  If not, we can delete it.
Assembler::~Assembler()
{
}

/**/
/*
Assembler::PassI()

NAME

	Assembler::PassI()

SYNOPSIS

	void Assembler::PassI()

DESCRIPTION

	This function establishes the location of the labels and performs the first 
    pass in the assembler. It will read each instruction and get its instruction
    type. If the instruction type is assembly or machine, load the location and 
    symbol into the symbol table.

RETURNS

	Nothing.

AUTHOR

	Andrew Ferrand

DATE

	12:58pm 11/19/2022

*/
/**/
void Assembler::PassI() 
{
    string a, b, c, d;
    SymbolTable table1;
    int loc = 0;        // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    for ( ; ; ) 
	{
        // Read the next line from the source file.
        string line; 
        if (!m_facc.GetNextLine(line)) 
		{
            // If there are no more lines, we are missing an end statement.
            return;
        }

        // Removing comments.
        int comment_loc;
        comment_loc = line.find(";");
        if (comment_loc != -1) 
        {
            line = line.substr(0, comment_loc);
        }

        // Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.ParseInstruction(line);

        // If this is an end statement, there is nothing left to do in Pass I.
        // Pass II will determine if the end is the last statement and report an error if it isn't.
        if (st == Instruction::ST_End) return;

        // Labels can only be on machine language and assembler language instructions.
        if (st == Instruction::ST_Comment)  
        {
        	continue;
	    }
        // If the instruction has a label, record it and its location in the symbol table
        if (m_inst.isLabel()) 
		{
            m_symtab.AddSymbol(m_inst.GetLabel(), loc);
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction(loc);
    }
}

/**/
/*
Assembler::PassII()

NAME

    Assembler::PassII()

SYNOPSIS

    void Assembler::PassII()

DESCRIPTION

    This function performs the second pass in the assembler. It will read each 
    instruction, do error reporting after the offending instruction line, and 
    prepare for the emulator. Translation of the program also occurs here. Errors 
    such as illegal operation code, undefined label, syntax errors, etc are 
	identified here.

RETURNS

    Nothing.

AUTHOR

    Andrew Ferrand

DATE

    1:02pm 11/19/2022

*/
/**/
void Assembler::PassII() 
{
	int numContents;			// Will hold the contents as a number.
	Errors errorList;
	errorList.InitErrorReporting();
	string label, opCode, operand, instruction;		// Variables we'll receive info from the instruction class.
	string contents;
	int tempLoc;

	// This will store the contents part for the translation table.
	static vector<string> m_Translation;
	m_facc.rewind();
	string a, b, c, d;
	SymbolTable table1;
	int loc = 0;        // Tracks the location of the instructions to be generated.
	string line, err;

	cout << "Translation of Program:\n\n";
	cout << "Location   Contents   Original Statement\n";

	// Successively process each line of source code.
	while (true) 
	{
		int errCount = 0;
		bool isError = false;

		// Read the next line from the source file.
		if (!m_facc.GetNextLine(line)) 
		{
			// If there are no more lines, reporting an error: missing an end statement.
			err = "Missing an end statement";
			errorList.RecordError(err);
			m_emul.emulatorErrCount++;
			errCount++;
			isError = true;
			errorList.DisplayErrors();
			return;
		}

		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(line);
		label = m_inst.getLabel();
		opCode = m_inst.getOpCode();
		operand = m_inst.getOperand();
		instruction = m_inst.getInstruction();

		// For each line, determine what type of line it is and translate it accordingly.
		// Processing a assembler instruction line.
		if (st == Instruction::ST_AssemblerInstr) 
		{
			// First part of contents - instruction code.
			if (opCode == "add") contents = "01";
			else if (opCode == "sub") contents = "02";
			else if (opCode == "mult") contents = "03";
			else if (opCode == "div") contents = "04";
			else if (opCode == "load") contents = "05";
			else if (opCode == "store") contents = "06";
			else if (opCode == "read") contents = "07";
			else if (opCode == "write") contents = "08";
			else if (opCode == "b") contents = "09";
			else if (opCode == "bm") contents = "10";
			else if (opCode == "bz") contents = "11";
			else if (opCode == "bp") contents = "12";
			else if (opCode == "halt") contents = "13";
			else 
			{
				contents = "00";
				err = "opcode does not exist";
				errorList.RecordError(err);
				m_emul.emulatorErrCount++;
				errCount++;
				isError = true;
			}
			if (opCode == "halt") 
			{
				contents += "0000";
				numContents = stoi(contents);
				m_emul.insertMemory(loc, numContents);
				cout << "  " << loc << "\t   " << contents << "\t" << instruction << endl;
			}
			else 
			{
				// Checking for multiply defined symbol.
				tempLoc = m_symtab.findLabelLoc(operand);
				if (tempLoc == -999) 
				{
					contents = contents + "?????";
					err = "multiply defined symbol";
					errorList.RecordError(err);
					m_emul.emulatorErrCount++;
					errCount++;
				}
				// Making sure the label exists in the table.
				else if (tempLoc < 0) 
				{
					contents = contents + "?????";
					err = "the label: " + operand + " was never defided";
					errorList.RecordError(err);
					m_emul.emulatorErrCount++;
					errCount++;
				}

				// Else all if fine.
				else 
				{
					stringstream conveting;
					conveting << setw(4) << setfill('0') << tempLoc;
					string s = conveting.str();
					contents += s;
				}
				numContents = stoi(contents);
				m_emul.insertMemory(loc, numContents);
				cout << "  " << loc << "\t   " << contents << "\t" << instruction << endl;
			}
		}
		// Processing a machine language line.
		else if (st == Instruction::ST_MachineLanguage) 
		{
			if (opCode == "dc") 
			{
				contents = "00";
				if (m_inst.getIfNumOperand()) 
				{
					int numericOperand = stoi(operand);
					stringstream conveting;
					conveting << setw(4) << setfill('0') << numericOperand;
					string s = conveting.str();
					contents += s;
				}
				else 
				{
					err = "operand is not numeric";
					errorList.RecordError(err);
					m_emul.emulatorErrCount++;
					errCount++;
					contents += "?????";
				}
				numContents = stoi(contents);
				m_emul.insertMemory(loc, numContents);
				cout << "  " << loc << "\t   " << contents << "\t" << instruction << endl;
			}
			else if (opCode == "ds") 
			{
				cout << "  " << loc << "\t   " << "       \t" << instruction << endl;
			}
			else if (opCode == "org") 
			{
				if (m_inst.getIfNumOperand()) 
				{
					int numLoc = stoi(operand);
					if (numLoc >= 0)
						cout << "  " << loc << "\t   " << "       \t" << instruction << endl;
					else 
					{
						err = "location must be greater than 0";
						errorList.RecordError(err);
						m_emul.emulatorErrCount++;
						errCount++;
						operand = "0";
						cout << "  " << loc << "\t   " << "       \t" << instruction << endl;
					}
				}
				else 
				{
					err = "an org must be followed by a positive number";
					errorList.RecordError(err);
					m_emul.emulatorErrCount++;
					errCount++;
					cout << "  " << loc << "\t   " << "       \t" << instruction << endl;
					operand = "0";
				}

			}
		}
		// Processing a comment line.
		else if (st == Instruction::ST_Comment) 
		{
			cout << "\t\t\t" << instruction << endl;
		}
		// Processing end line.
		else if (st == Instruction::ST_End) 
		{
			// Making sure there are no other statements after the end statement.
			if (m_facc.GetNextLine(line))
			{
				err = "Statment after end statment";
				errorList.RecordError(err);
				m_emul.emulatorErrCount++;
				errCount++;
			}
			cout << "\t\t\t" << instruction << endl;
			return;
		}
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
		{
			continue;
		}
		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);

		// If any errors occur, display them
		if (errCount)
		{
			errorList.DisplayErrors();
		}
	}
}

/**/
/*
Assembler::RunProgramInEmulator()

NAME

	Assembler::RunProgramInEmulator()

SYNOPSIS

	void Assembler::RunProgramInEmulator()

DESCRIPTION

	This function runs the emulator which simulates the VC407.

RETURNS

	Nothing.

AUTHOR

	Andrew Ferrand

DATE

	4:20pm 12/03/2022

*/
/**/
void Assembler::RunProgramInEmulator()
{
	if (m_emul.emulatorErrCount) 
	{
		cout << "Emulator is unable to run due to errors.\n";
	}
	else
	{
		m_emul.runProgram();
	}
}