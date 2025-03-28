@echo off
setlocal

REM Get the directory of the batch file
set SCRIPT_DIR=%~dp0

REM Change to the script directory
cd /d "%SCRIPT_DIR%"

IF EXIST "MIPS_Interpreter.exe" (
    echo Removing old MIPS_Interpreter.exe...
    del "MIPS_Interpreter.exe"
) 

echo Compiling MIPS Interpreter...
gcc ADD.c ADDI.c AND.c ANDI.c BEQ.c BNE.c DIV.c LUI.c LW.c MFHI.c MFLO.c ^
MIPS_Instruction.c MIPS_Interpreter.c MULT.c OR.c ORI.c SLT.c SLTI.c SUB.c SW.c ^
-o MIPS_Interpreter.exe
echo Done!

echo Running MIPS Interpreter...
start MIPS_Interpreter.exe