/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** Emulator
*/

#include "Emulator.hpp"

Emulator::Emulator(std::string gamepath) : _gamepath(gamepath)
{
    std::cout << "Emulator: Starting with " << this->_gamepath << std::endl;
}

Emulator::~Emulator()
{
    std::cout << "Emulator: Ending" << std::endl;
}
