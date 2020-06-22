/*
** EPITECH PROJECT, 2020
** CHIP_8_Emulator
** File description:
** file
*/

#ifndef CHIP_8_EMULATOR_APPLICATION_HPP
#define CHIP_8_EMULATOR_APPLICATION_HPP

#include "Emulator.hpp"
#include "include.hpp"
#include "Error.hpp"

class Application
{
    public:
        Application(int argc, char **argv);
        ~Application();
        void Run();
        void displayRegisters(const struct registers &_registers, short opcode, size_t action);
        std::string Usage(const std::string &binary);
    private:
        sf::RenderWindow window;
        sf::Event event;
        sf::Clock deltaClock;
        std::unique_ptr<Emulator> emulator;
        sf::Clock clock;
        bool can_continue = false;
        sf::SoundBuffer buffer;
        sf::Sound sound;
        std::string binary_name;
};

#endif //CHIP_8_EMULATOR_APPLICATION_HPP
