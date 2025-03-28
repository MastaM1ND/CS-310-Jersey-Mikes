/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void slti_immd_assm(void) {
    if (strcmp(OP_CODE, "SLTI") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Checking the type of parameters
    */
    // The first parameter should be a register (destination)
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // The second parameter needs to be a register (source)
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // The third parameter needs to be an immediate
    if (PARAM3.type != IMMEDIATE) {
        state = INVALID_PARAM;
        return;
    }

    /*
        Checking the value of parameters
    */
    // Destination register (rt) must be 31 or less
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    // Source register (rs) must be 31 or less
    if (PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }

    // Immediate value is limited to 16 bits (0xFFFF)
    if (PARAM3.value > 0xFFFF) {
        state = INVALID_IMMED;
        return;
    }

    /*
        Putting the binary together for SLTI (I-type):
        Opcode (bits 31..26) = 001010
        Rs (bits 25..21)     = PARAM2.value (source register)
        Rt (bits 20..16)     = PARAM1.value (destination register)
        Immediate (bits 15..0)= PARAM3.value
    */

    // Set the opcode
    setBits_str(31, "001010");

    // Set Rt (destination register)
    setBits_num(20, PARAM1.value, 5);

    // Set Rs (source register)
    setBits_num(25, PARAM2.value, 5);

    // Set immediate
    setBits_num(15, PARAM3.value, 16);

    // Tell the system the encoding is done
    state = COMPLETE_ENCODE;
}

void slti_immd_bin(void) {
    // Check if the opcode bits match for SLTI
    if (checkBits(31, "001010") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Extracting values from the binary:
        - Rs: bits 25..21 (source register)
        - Rt: bits 20..16 (destination register)
        - Immediate: bits 15..0
    */
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);
    uint32_t imm16 = getBits(15, 16);

    /*
        Setting Instruction values:
        For SLTI, the assembly syntax is "SLTI rt, rs, immediate"
        where rt is the destination register, rs is the source register,
        and immediate is the 16-bit constant.
    */
    setOp("SLTI");
    setParam(1, REGISTER, Rt);      // destination register
    setParam(2, REGISTER, Rs);      // source register
    setParam(3, IMMEDIATE, imm16);  // immediate operand

    // Tell the system the decoding is done
    state = COMPLETE_DECODE;
}


