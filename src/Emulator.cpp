/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** Emulator
*/

#include "Emulator.hpp"

Emulator::Emulator(std::string gamepath, sf::RenderWindow &window)
: _gamepath(gamepath),
_window(window)
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
        _memory[i] = 0;
    for (int i = 0; i < 16; i++)
        _stack[i] = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        _display[i] = 1;
}

Emulator::~Emulator()
{
    std::cout << "Emulator: Ending" << std::endl;
}

void Emulator::displayVideo()
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        if (i % WIDTH == 0) {
            if (i > WIDTH)
                y++;
            x = 0;
        }
        sf::FloatRect rectangle(x * PIXEL_SIZE, y * PIXEL_SIZE + PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE);
        if (this->_display[i] == 1)
            ImGui::DrawRectFilled(rectangle, sf::Color::White);
        else if (this->_display[i] == 0)
            ImGui::DrawRectFilled(rectangle, sf::Color::Black);
        else
            ImGui::DrawRectFilled(rectangle, sf::Color::Red);
        x++;
    }
}