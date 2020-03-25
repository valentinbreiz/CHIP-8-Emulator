/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** Emulator
*/

#pragma once

#include <string>
#include <iostream>

struct registers
{
    unsigned char V[16]; //registers
    unsigned short I; //index register
    unsigned short PC; //program counter
    unsigned char SP; //stack pointer
    unsigned char timer_delay;
    unsigned char timer_sound;
};

class Emulator
{
    unsigned char fonts[80] = { 
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    public:
        Emulator(std::string gamepath);
        ~Emulator();
        const struct registers &getRegisters() { return (this->_registers); }
    protected:
    private:
        std::string _gamepath;
        struct registers _registers;
        unsigned char memory[4096];
        unsigned short stack[16];
        unsigned char keys[16];
        unsigned char display[64 * 32];
};
