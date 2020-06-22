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
#include <SFML/Audio.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_memory_editor.h"
#include <fstream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/kd.h>
#include "Error.hpp"
#include "Opcodes.hpp"

#define HEIGHT 32
#define WIDTH 64
#define PIXEL_SIZE 9
#define START_ADDRESS 0x200

struct registers
{
    unsigned char V[16]; //registers
    unsigned short I; //index register
    unsigned short PC; //program counter
    unsigned char SP; //stack pointer
    unsigned char DT; //Timer Delay
    unsigned char ST; //Timer Sound
};

struct opcode
{ 
    unsigned short masque;
    unsigned short id;
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
        Emulator(std::string gamepath, sf::RenderWindow &window, sf::Sound &sound);
        ~Emulator();
        const struct registers &getRegisters() { return (this->_registers); }
        const unsigned short &getOpcode() { return (this->_opcode); }
        const size_t &getAction() { return (this->_action); }
        void displayVideo();
        void displayDump();
        void executeOperation();
        void openFile(std::string gamepath);
        void initRegistersMemory();
        size_t GetPointOffset(size_t x, size_t y);
        void setKey(unsigned char key, bool state);

        std::string _gamepath;
        sf::RenderWindow &_window;
        sf::Sound &_sound;
        struct registers _registers;
        unsigned char _memory[4096];
        unsigned short _stack[16];
        unsigned char _keys[16];
        unsigned char _display[WIDTH * HEIGHT];
        unsigned short _opcode;
        size_t _action;
        struct opcode opcodes[35];

        std::shared_ptr<Opcodes> machine;
    protected:
    private:
};
