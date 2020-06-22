/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** Opcodes
*/

#include "Opcodes.hpp"

Opcodes::Opcodes()
{
}

Opcodes::~Opcodes()
{

}

Opcodes::TArithActionFunc Opcodes:: m_actionFcns[TAction::count] = {

    &Opcodes::opcode_0NNN,
    &Opcodes::opcode_00E0,
    &Opcodes::opcode_00EE,
    &Opcodes::opcode_1NNN,
    &Opcodes::opcode_2NNN,
    &Opcodes::opcode_3XNN,
    &Opcodes::opcode_4XNN,
    &Opcodes::opcode_ANNN,
    &Opcodes::opcode_BNNN,
    &Opcodes::opcode_CXNN,
    &Opcodes::opcode_DXYN,
    &Opcodes::opcode_EX9E,
    &Opcodes::opcode_EXA1,
    &Opcodes::opcode_FX07,
    &Opcodes::opcode_FX0A,
    &Opcodes::opcode_FX15,
    &Opcodes::opcode_FX18,
    &Opcodes::opcode_FX1E,
    &Opcodes::opcode_FX29,
    &Opcodes::opcode_FX33,
    &Opcodes::opcode_FX55,
    &Opcodes::opcode_FX65
};

void Opcodes::opcode_0NNN(unsigned char b1, unsigned char b2, unsigned char b3)
{

}

void Opcodes::opcode_00E0(unsigned char b1, unsigned char b2, unsigned char b3)
{
    for (int i = 0; i < HEIGHT * WIDTH; i++)
        this->_display[i] = 0;
    this->_registers.PC += 2;
}

void Opcodes::opcode_00EE(unsigned char b1, unsigned char b2, unsigned char b3)
{
    if (this->_registers.SP > 0) {
        this->_registers.SP--;
        this->_registers.PC = this->_stack[this->_registers.SP];
        this->_registers.PC += 2;
    }
}

void Opcodes::opcode_1NNN(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_registers.PC = (b3 << 8) + (b2 << 4) + b1;
}

void Opcodes::opcode_2NNN(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_stack[this->_registers.SP] = this->_registers.PC;
    if (this->_registers.SP < 15)
        this->_registers.SP++;
    this->_registers.PC = (b3 << 8) + (b2 << 4) + b1;
}

void Opcodes::opcode_3XNN(unsigned char b1, unsigned char b2, unsigned char b3)
{
    if (this->_registers.V[b3] == ((b2 << 4) + b1))
        this->_registers.PC += 4;
    else
        this->_registers.PC += 2;
}

void Opcodes::opcode_4XNN(unsigned char b1, unsigned char b2, unsigned char b3)
{
    if (this->_registers.V[b3] == ((b2 << 4) + b1))
        this->_registers.PC += 2;
    else
        this->_registers.PC += 4;
}

void Opcodes::opcode_5XY0(unsigned char b1, unsigned char b2, unsigned char b3)
{
    
}

void Opcodes::opcode_6XNN(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_registers.V[b3] = (b2 << 4) + b1;
    this->_registers.PC += 2;
}

void Opcodes::opcode_7XNN(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_registers.V[b3] += + (b2 << 4) + b1;
    this->_registers.PC += 2;
}

void Opcodes::opcode_8XY0(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_registers.V[b3] = this->_registers.V[b2];
    this->_registers.PC += 2;
}

void Opcodes::opcode_8XY1(unsigned char b1, unsigned char b2, unsigned char b3)
{

}
void Opcodes::opcode_8XY2(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_registers.V[b3] &= this->_registers.V[b2];
    this->_registers.PC += 2;
}

void Opcodes::opcode_BXY3(unsigned char b1, unsigned char b2, unsigned char b3)
{

}

void Opcodes::opcode_8XY4(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_registers.V[b3] += this->_registers.V[b2];
    if (this->_registers.V[b2] > (0xFF - this->_registers.V[b3]))
        this->_registers.V[0xF] = 1;
    else
        this->_registers.V[0xF] = 0;
    this->_registers.PC += 2;
}

void Opcodes::opcode_8XY5(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_registers.V[b3] -= this->_registers.V[b2];
    if (this->_registers.V[b2] < (this->_registers.V[b3]))
        this->_registers.V[0xF] = 1;
    else
        this->_registers.V[0xF] = 0;
    this->_registers.PC += 2;
}

void Opcodes::opcode_8XY6(unsigned char b1, unsigned char b2, unsigned char b3)
{

}

void Opcodes::opcode_8XY7(unsigned char b1, unsigned char b2, unsigned char b3)
{

}

void Opcodes::opcode_8XYE(unsigned char b1, unsigned char b2, unsigned char b3)
{

}

void Opcodes::opcode_9XY0(unsigned char b1, unsigned char b2, unsigned char b3)
{

}

void Opcodes::opcode_ANNN(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_registers.I = (b3 << 8) + (b2 << 4) + b1;
    this->_registers.PC += 2;
}

void Opcodes::opcode_BNNN(unsigned char b1, unsigned char b2, unsigned char b3)
{

}

void Opcodes::opcode_CXNN(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_registers.V[b3] = ((rand() % 0xFF) & ((b2 << 4) + b1));
    this->_registers.PC += 2;
}

void Opcodes::opcode_DXYN(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_registers.V[0x0F] = 0;
    unsigned short pixel;
    for (unsigned char k = 0; k < b1; ++k){
        pixel = this->_memory[this->_registers.I + k];
        for (unsigned char j = 0; j < 8; ++j) {
            int x = (this->_registers.V[b3] + j) % WIDTH;
            int y = (this->_registers.V[b2] + k) % HEIGHT;
            if ((pixel & (0x80 >> j)) != 0) {
                if (this->_display[GetPointOffset(x, y)] == 0) {
                    this->_registers.V[0xF] = 1;
                    this->_display[GetPointOffset(x, y)] = 1;
                }
                else {
                    this->_display[GetPointOffset(x, y)] = 0;
                    //this->_registers.V[0xF] = 1;
                }
            }
        }
    }
    this->_registers.PC += 2;
}

void Opcodes::opcode_EX9E(unsigned char b1, unsigned char b2, unsigned char b3)
{

}

void Opcodes::opcode_EXA1(unsigned char b1, unsigned char b2, unsigned char b3)
{
    if (!this->_keys[this->_registers.V[b3]])
        this->_registers.PC += 4;
    else
        this->_registers.PC += 2;
}

void Opcodes::opcode_FX07(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_registers.V[b3] = this->_registers.DT;
    this->_registers.PC += 2;
}

void Opcodes::opcode_FX0A(unsigned char b1, unsigned char b2, unsigned char b3)
{

}

void Opcodes::opcode_FX15(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_registers.DT = this->_registers.V[b3];
    this->_registers.PC += 2;
}

void Opcodes::opcode_FX18(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_registers.ST = this->_registers.V[b3];
    this->_registers.PC += 2;
}

void Opcodes::opcode_FX1E(unsigned char b1, unsigned char b2, unsigned char b3)
{

}

void Opcodes::opcode_FX29(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_registers.I = this->_registers.V[b3] * 0x05;
    this->_registers.PC += 2;
}

void Opcodes::opcode_FX33(unsigned char b1, unsigned char b2, unsigned char b3)
{
    this->_memory[this->_registers.I] = this->_registers.V[b3] / 100;
    this->_memory[this->_registers.I + 1] = (this->_registers.V[b3] / 10) % 10;
    this->_memory[this->_registers.I + 1] = (this->_registers.V[b3] % 10) % 10;
    this->_registers.PC += 2;
}

void Opcodes::opcode_FX55(unsigned char b1, unsigned char b2, unsigned char b3)
{

}

void Opcodes::opcode_FX65(unsigned char b1, unsigned char b2, unsigned char b3)
{
    for (int i = this->_registers.I; i < b3; i++)
        this->_registers.V[i] = this->_memory[this->_registers.I + i];
    this->_registers.PC += 2;
}

size_t Opcodes::GetPointOffset(size_t x, size_t y)
{
    return ((y * WIDTH) + x);
}