/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "MIPS_Instruction.h"

void mult_reg_assm(void) {
    // Verify correct opcode string
    if (strcmp(OP_CODE, "MULT") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Checking the type of parameters
    */
    // MULT expects 2 registers: PARAM1, PARAM2

    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    if (PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // If a third parameter is provided, it's invalid for MULT
    if (PARAM3.type != EMPTY) {
        state = INVALID_REG;
        return;
    }

    /*
        Checking the value of parameters
    */
    // Both registers must be 31 or less
    if (PARAM1.value > 31 || PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }

    /*
        Putting the binary together for MULT (R-type):
        Opcode (bits 31..26) = 000000
        Rs (bits 25..21)     = PARAM1.value
        Rt (bits 20..16)     = PARAM2.value
        Rd (bits 15..11)     = 0
        shamt (bits 10..6)   = 0
        funct (bits 5..0)    = 011000 (decimal 24)
    */

    // Set the opcode
    setBits_str(31, "000000");

    // Set Rs
    setBits_num(25, PARAM1.value, 5);

    // Set Rt
    setBits_num(20, PARAM2.value, 5);

    // Rd = 0
    setBits_num(15, 0, 5);

    // shamt = 0
    setBits_num(10, 0, 5);

    // funct = 011000
    setBits_str(5, "011000");

    // Encoding done
    state = COMPLETE_ENCODE;
}

void mult_reg_bin(void) {
    /*
        Checking opcode (bits 31..26) and funct (bits 5..0)
    */
    if (checkBits(31, "000000") != 0) {
        state = WRONG_COMMAND;
        return;
    }
    if (checkBits(5, "011000") != 0) {
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
        The MULT instruction does not have a destination register (Rd)
        The MULT Syntax is MULT Rs, Rt
        The result is stored in the HI and LO registers
    */
    setOp("MULT");
    setParam(1, REGISTER, Rs); // first source register
    setParam(2, REGISTER, Rt); // second source register

    // Decoding done
    state = COMPLETE_DECODE;
}
