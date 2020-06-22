/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** Opcodes
*/

#include "Opcodes.hpp"

Opcodes::Opcodes(std::shared_ptr<Emulator> emulator)
{
    this->_emulator = emulator;
}

Opcodes::~Opcodes()
{

}

Opcodes::TArithActionFunc Opcodes:: m_actionFcns[TAction::count] = {
    &Opcodes::opcode_0NNN,
    &Opcodes::opcode_00E0,
    &Opcodes::opcode_00EE,
    //todo add other opcodes
};

void Opcodes::opcode_0NNN()
{

}

void Opcodes::opcode_00E0()
{
    for (int i = 0; i < HEIGHT * WIDTH; i++)
        _emulator->_display[i] = 0;
    _emulator->_registers.PC += 2;
}

void Opcodes::opcode_00EE()
{
    if (_emulator->_registers.SP > 0) {
        _emulator->_registers.SP--;
        _emulator->_registers.PC = _emulator->_stack[_emulator->_registers.SP];
        _emulator->_registers.PC += 2;
    }
}