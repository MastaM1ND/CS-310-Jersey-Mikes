#include "Instruction.h"

void or_reg_assm(void)
{
	// Check if the operation code matches "OR"
	if (strcmp(OP_CODE, "OR") != 0)
	{
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// PARAM1 should be a register
	if (PARAM1.type != REGISTER)
	{
		state = MISSING_REG;
		return;
	}

	// PARAM2 should be a register
	if (PARAM2.type != REGISTER)
	{
		state = MISSING_REG;
		return;
	}

	// PARAM3 should be a register
	if (PARAM3.type != REGISTER)
	{
		state = MISSING_REG;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// Rd should be 31 or less
	if (PARAM1.value > 31)
	{
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31)
	{
		state = INVALID_REG;
		return;
	}

	// Rt should be 31 or less
	if (PARAM3.value > 31)
	{
		state = INVALID_REG;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_num(31, 0, 6);

	// Set the funct
	setBits_str(5, "100101");

	// Set 10-6 as 0s
	setBits_num(10, 0, 5);

	// Set Rd
	setBits_num(15, PARAM1.value, 5);

	// Set Rs
	setBits_num(25, PARAM2.value, 5);

	// Set Rt
	setBits_num(20, PARAM3.value, 5);

	// Tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void or_reg_bin(void)
{
	/*
		Checking the opcode and funct bits
	*/

	// Check if the opcode and funct bits match
	if (checkBits(31, "000000") != 0 || checkBits(5, "100101") != 0)
	{
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values in the binary
	*/

	// Get Rd from bits 15-11
	uint32_t Rd = getBits(15, 5);

	// Get Rs from bits 25-21
	uint32_t Rs = getBits(25, 5);

	// Get Rt from bits 20-16
	uint32_t Rt = getBits(20, 5);

	/*
		Setting instruction values
	*/

	// Set the operation to "OR"
	setOp("OR");

	// Set PARAM1 as Rd
	setParam(1, REGISTER, Rd);

	// Set PARAM2 as Rs
	setParam(2, REGISTER, Rs);

	// Set PARAM3 as Rt
	setParam(3, REGISTER, Rt);

	// Tell the system the decoding is done
	state = COMPLETE_DECODE;
}
