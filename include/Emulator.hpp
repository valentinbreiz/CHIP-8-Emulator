/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** Emulator
*/

#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_memory_editor.h"
#include <fstream>

#define HEIGHT 32
#define WIDTH 64
#define PIXEL_SIZE 9

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
        Emulator(std::string gamepath, sf::RenderWindow &window);
        ~Emulator();
        const struct registers &getRegisters() { return (this->_registers); }
        void displayVideo();
        void displayDump();
    protected:
    private:
        std::string _gamepath;
        sf::RenderWindow &_window;
        struct registers _registers;
        unsigned char _memory[4096];
        unsigned short _stack[16];
        unsigned char _keys[16];
        unsigned char _display[WIDTH * HEIGHT];
};
