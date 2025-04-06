/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

/*
	Encodes the LUI instruction into binary format.
*/
void lui_immd_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) returns 0 if they match
	if (strcmp(OP_CODE, "LUI") != 0) {
		// If the op code doesn't match, this isn't the correct command
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	//PARAM 3 REMOVED, ONLY NEEDS 2 PARAMETERS

	// The first parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// The second parameter should be an immediate
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// The register value should be 31 or less
	if (PARAM1.value > 31) {
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
	setBits_str(31, "001111");

	// Set the destination register
	setBits_num(20, PARAM1.value, 5);

	// Set the source register (always 0 for LUI)
	setBits_num(25, 0, 5);

	// Set the immediate value
	setBits_num(15, PARAM2.value, 16);

	// Tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

/*
	Decodes the binary representation of the LUI instruction.
*/
void lui_immd_bin(void) {
	// Check if the op code bits match
	// checkBits(start_bit, bit_string) returns 0 if the bit_string matches
	if (checkBits(31, "001111") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read as correctly

	/*
		Finding values in the binary
	*/

	// getBits(start_bit, width)
	uint32_t Rs = getBits(25, 5); // Source register (should always be 0 for LUI)
	uint32_t Rt = getBits(20, 5); // Destination register
	uint32_t imm16 = getBits(15, 16); // Immediate value

	/*
		Setting instruction values
	*/

	setOp("LUI");
	// setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); // Destination register
	setParam(2, IMMEDIATE, imm16); // Immediate operand

	// Tell the system the decoding is done
	state = COMPLETE_DECODE;
}
