/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** Emulator
*/

#pragma once

#include <string>
#include <iostream>

class Emulator
{
    public:
        Emulator(std::string gamepath);
        ~Emulator();

    protected:
    private:
        std::string _gamepath;
};
