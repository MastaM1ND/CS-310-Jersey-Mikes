/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void div_reg_assm(void) {
	// Checking that the op code matches
		// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "DIV") != 0) {
		// If the op code doesnt match, this isnt the correct command
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// The first parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	// Param 2 needs to be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// Rt should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "000000");
	//set rt
	setBits_num(20, PARAM1.value, 5);
	// set rs
	setBits_num(25, PARAM2.value, 5);
	// set funct
	setBits_str(5, "011010");
	//set offset
	setBits_num(15, 0, 10);
	
	state = COMPLETE_ENCODE;
}

void div_reg_bin(void) {
	/*
        Checking opcode (bits 31..26) and funct (bits 5..0)
    */
	if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
        Extracting register fields
    */
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	/*
        Setting instruction values
        The DIV instruction does not have a destination register (Rd)
        The DIV Syntax is DIV Rs, Rt
        The result is stored in the HI and LO registers
    */
	setOp("DIV");
	setParam(2, REGISTER, Rs);
	setParam(1, REGISTER, Rt);

	state = COMPLETE_DECODE;
}


