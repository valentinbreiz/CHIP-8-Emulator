/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** Emulator
*/

#pragma once

#include <string>
#include <iostream>
#include <memory>
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
        const struct registers &getRegisters() { return (machine->_registers); }
        const unsigned short &getOpcode() { return (machine->_opcode); }
        const size_t &getAction() { return (machine->_action); }
        void displayVideo();
        void displayDump();
        void executeOperation();
        void openFile(std::string gamepath);
        void initRegistersMemory();
        void setKey(unsigned char key, bool state);

        std::shared_ptr<Opcodes> machine;
    protected:
    private:
        sf::RenderWindow &_window;
        sf::Sound &_sound;
};