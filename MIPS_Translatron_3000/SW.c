/*
 * Author: Ol' Jim
 * Date: 06/13/2012
 * ByteForge Systems
 * MIPS-Translatron 3000
 */

#include "Instruction.h" // Include the header file that defines necessary structures and functions

// Function to assemble the "SW" (store word) instruction from its components
void sw_immd_assm(void)
{
	// Check if the operation code (OP_CODE) matches "SW"
	if (strcmp(OP_CODE, "SW") != 0)
	{
		state = WRONG_COMMAND; // Set state to indicate an incorrect command
		return;
	}

	// Validate that the first parameter (PARAM1) is a register
	if (PARAM1.type != REGISTER)
	{
		state = MISSING_REG; // Set state to indicate a missing register
		return;
	}

	// Validate that the second parameter (PARAM2) is an immediate value
	if (PARAM2.type != IMMEDIATE)
	{
		state = INVALID_PARAM; // Set state to indicate an invalid parameter
		return;
	}

	// Validate that the third parameter (PARAM3) is a register
	if (PARAM3.type != REGISTER)
	{
		state = MISSING_REG; // Set state to indicate a missing register
		return;
	}

	// Check if the first register value is within valid bounds (0-31)
	if (PARAM1.value > 31)
	{
		state = INVALID_REG; // Set state to indicate an invalid register
		return;
	}

	// Check if the immediate value is within valid bounds (16-bit value)
	if (PARAM2.value > 0xFFFF)
	{
		state = INVALID_IMMED; // Set state to indicate an invalid immediate value
		return;
	}

	// Check if the third register value is within valid bounds (0-31)
	if (PARAM3.value > 31)
	{
		state = INVALID_REG; // Set state to indicate an invalid register
		return;
	}

	// Encode the instruction into binary format
	setBits_str(31, "101011");		   // Set the opcode for "SW" (store word)
	setBits_num(20, PARAM1.value, 5);  // Set the first register (Rt)
	setBits_num(15, PARAM2.value, 16); // Set the immediate value (offset)
	setBits_num(25, PARAM3.value, 5);  // Set the second register (Rs)

	state = COMPLETE_ENCODE; // Set state to indicate successful encoding
}

// Function to decode a binary "SW" (store word) instruction into its components
void sw_immd_bin(void)
{
	// Check if the binary opcode matches "SW"
	if (checkBits(31, "101011") != 0)
	{
		state = WRONG_COMMAND; // Set state to indicate an incorrect command
		return;
	}

	// Extract the components of the instruction from the binary representation
	uint32_t Rs = getBits(25, 5);	   // Extract the second register (Rs)
	uint32_t Rt = getBits(20, 5);	   // Extract the first register (Rt)
	uint32_t offset = getBits(15, 16); // Extract the immediate value (offset)

	// Set the decoded components into their respective parameters
	setOp("SW");					// Set the operation code to "SW"
	setParam(1, REGISTER, Rt);		// Set the first parameter as a register (Rt)
	setParam(2, IMMEDIATE, offset); // Set the second parameter as an immediate value (offset)
	setParam(3, REGISTER, Rs);		// Set the third parameter as a register (Rs)
	// FLip the order of the offset and Rs to match the assembly function

	state = COMPLETE_DECODE; // Set state to indicate successful decoding
}