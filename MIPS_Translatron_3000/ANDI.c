#include "Instruction.h"

void andi_immd_assm(void) {

	// Checking that the op code matches
	if (strcmp(OP_CODE, "ANDI") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// check the type of parameters

	//first parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// second parameter should be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// third parameter should be an immediate
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	// check the value of parameters

	// first parameter should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// second parameter should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// third parameter should be 16 bits
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	// combine binary

	// set the opcode
	setBits_str(31, "001100");
	// param1 is the rt value
	setBits_num(20, PARAM1.value, 5);
	// param2 is the rs value
	setBits_num(25, PARAM2.value, 5);
	// param3 is the immediate value
	setBits_num(15, PARAM3.value, 16);

	state = COMPLETE_ENCODE;
}

void andi_immd_bin(void) {
	// Check the opcode
	if (checkBits(31, "001100") != 0 ) {
		state = WRONG_COMMAND;
		return;
	}

	// get binary values

	//get Rs getBits(start, size)
	uint32_t Rs = getBits(25, 5);

	//get Rt getBits(start, size)
	uint32_t Rt = getBits(20, 5);

	//get immediate getBits(start, size)
	uint32_t imm16 = getBits(15, 16);

	// set operation
	setOp("ANDI");

	// set parameters
	// setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); 
	setParam(2, REGISTER, Rs); 
	setParam(3, IMMEDIATE, imm16);
	
	state = COMPLETE_DECODE;
}



