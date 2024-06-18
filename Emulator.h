//
//		Emulator class - supports the emulation of VC407 programs
//
#ifndef _EMULATOR_H      // UNIX way of preventing multiple inclusions.
#define _EMULATOR_H

class emulator 
{

public:

    int emulatorErrCount = 0;
    const static int MEMSZ = 10'000;	// The size of the memory of the VC407.
    emulator() 
    {
        memset(m_memory, 0, MEMSZ * sizeof(int));
    }
    // Records instructions and data into simulated memory.
    bool insertMemory(int a_location, long long a_contents); //possibly change long long to int
    
    // Runs the program recorded in memory.
    bool runProgram();

private:
    // Memory for the VC407
    int m_memory[MEMSZ] = {};	// initialize all spots to 0.
    int accumulator;
};

#endif

