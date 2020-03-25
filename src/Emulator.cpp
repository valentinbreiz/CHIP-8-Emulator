/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** Emulator
*/

#include "Emulator.hpp"

Emulator::Emulator(std::string gamepath)
: _gamepath(gamepath)
{
    std::cout << "Emulator: Starting with " << this->_gamepath << std::endl;
    for (int i = 0; i < 16; i++)
        this->_registers.V[i] = 0;
    this->_registers.I = 0;
    this->_registers.PC = 0;
    this->_registers.SP = 0;
    this->_registers.timer_delay = 0;
    this->_registers.timer_sound = 0;
    for (int i = 0; i < 4096; i++)
        memory[i] = 0;
    for (int i = 0; i < 16; i++)
        stack[i] = 0;
    for (int i = 0; i < 64 * 32; i++)
        display[i] = 0;
}

Emulator::~Emulator()
{
    std::cout << "Emulator: Ending" << std::endl;
}
