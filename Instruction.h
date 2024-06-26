//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//

#ifndef _INSTRUCTION_N
#define _INSTRUCTION_N

#include <sstream>
#include <string>

#pragma once

// The elements of an instruction.
class Instruction 
{

public:

    Instruction();
    ~Instruction();

    // Codes to indicate the type of instruction we are processing.  Why is this inside the
    // class?  We should make this an enum class.  We will do this during a lecture.
    enum InstructionType 
    {
        ST_MachineLanguage, 	// A machine language instruction.
        ST_AssemblerInstr,      // Assembler Language instruction.
        ST_Comment,             // Comment or blank line
        ST_End                  // end instruction.
    };
    // Parse the Instruction.
    InstructionType ParseInstruction(string a_line);

    // Compute the location of the next instruction.
    int LocationNextInstruction(int a_loc);

    // To access the label.
    inline string& GetLabel() 
    {
        return m_Label;
    };

    // To determine if a label is blank.
    inline bool isLabel() 
    {
        return !m_Label.empty();
    };

    // Label getter.
    string getLabel() 
    {
        return m_Label;
    }
    // OpCode getter.
    string getOpCode()
    {
        return m_OpCode;
    }
    // Operand getter.
    string getOperand()
    {
        return m_Operand;
    }
    // Original line of instruction getter.
    string getInstruction()
    {
        return m_instruction;
    }
    // Returns true of operand is numerical. False otherwise.
    bool getIfNumOperand()
    {
        return m_IsNumericOperand;
    }

private:


    // The elemements of a instruction
    string m_Label;        // The label.
    string m_OpCode;       // The symbolic op code.
    string m_Operand;     // The first operand. 


    string m_instruction;    // The original instruction.

    // Derived values.
    int m_NumOpCode;     // The numerical value of the op code for machine language equivalents.
    InstructionType m_type; // The type of instruction.
    
    bool m_IsNumericOperand; // == true if the operand 1 is numeric.
    int m_OperandValue;   // The value of the operand 1 if it is numeric.
    
};
#endif