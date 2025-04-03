/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void lw_immd_assm(void) {
	// Checking that the op code matches
		// strcmp(string1, string2) returns 0 if they match
	if (strcmp(OP_CODE, "LW") != 0) {
		// If the op code doesn't match, this isn't the correct command
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

	// The second parameter should be an immediate
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_IMMED;
		return;
	}

	// The third parameter should be a register
	if (PARAM3.type != REGISTER) {
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
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	// The immediate value is limited to 16 bits, this is 0xFFFF
	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "100011");

	// Set Rt
	setBits_num(20, PARAM1.value, 5);

	// Set immediate value
	setBits_num(15, PARAM2.value, 16);

	// Set Rs
	setBits_num(25, PARAM3.value, 5);

	// Tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void lw_immd_bin(void) {
	// Check if the op code bits match
		// checkBits(start_bit, bit_string) returns 0 if the bit_string matches
		// Any x will be skipped
		// If the manual shows (0), then the value of that bit doesn't matter
	if (checkBits(31, "100011") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read as correctly

	/*
		Finding values in the binary
	*/

	// getBits(start_bit, width)
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	/*
		Setting Instruction values
	*/

	setOp("LW");
	// setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); // destination
	setParam(2, IMMEDIATE, imm16); // immediate operand
	setParam(3, REGISTER, Rs); // source register operand

	// Tell the system the decoding is done
	state = COMPLETE_DECODE;
}
