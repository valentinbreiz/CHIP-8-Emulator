/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** utils
*/

#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <string>
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

template <class T>
std::string to_hex(T t, std::ios_base & (*f)(std::ios_base&))
{
    std::ostringstream oss;

    oss << std::uppercase << f << t;
    return oss.str();
}

void displayRegisters(const struct registers &_registers, short opcode, size_t action);