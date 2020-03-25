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
    std::ifstream game; 
	size_t size = 0;
	game.open(gamepath, std::ios::in | std::ios::binary | std::ios::ate);
	if (game.is_open()) {
		char* data = NULL;
		game.seekg(0, std::ios::end);
		size = game.tellg();
		game.seekg(0, std::ios::beg);
		data = new char[size+1];
		game.read(data, size);
        data = &data[1];
		data[size] = '\0';
        for (int i = 0; i < size; i++)
            _memory[0x200 + i] = data[i];
	}
    else {
        std::cerr << "Error loading file." << std::endl;
        exit(84);
    }
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
            y++;
            x = 0;
        }
        sf::FloatRect rectangle(x * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE);
        if (this->_display[i] == 1)
            ImGui::DrawRectFilled(rectangle, sf::Color::White);
        else if (this->_display[i] == 0)
            ImGui::DrawRectFilled(rectangle, sf::Color::Black);
        else
            ImGui::DrawRectFilled(rectangle, sf::Color::Red);
        x++;
    }
}

void Emulator::displayDump()
{
    static MemoryEditor memory;
    memory.DrawWindow("Heap Memory Dump", this->_memory, 4096);
    static MemoryEditor display;
    display.DrawWindow("Video RAM Dump", this->_display, WIDTH * HEIGHT);
    static MemoryEditor stack;
    stack.DrawWindow("Stack Dump", this->_stack, 16);
}