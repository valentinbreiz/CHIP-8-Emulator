/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** main
*/

#include "Emulator.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "include.hpp"

int main(int argc, char **argv)
{
    std::string title;
    sf::RenderWindow window;
    sf::Event event;
    sf::Clock deltaClock;
    std::unique_ptr<Emulator> emulator;

    if (argc != 2) {
        std::cerr << "USAGE: " << argv[0] << "game.ch8" << std::endl;
        return (84);
    }

    title = "CHIP-8 Emulator : " + std::string(argv[1]);
    window.create(sf::VideoMode(800, 600), title);
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    emulator = std::make_unique<Emulator>(argv[1]);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        displayRegisters(emulator->getRegisters());
        ImGui::End();
        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}

void displayRegisters(const struct registers &_registers)
{
    ImGui::Begin("Registers values");
    for (int i = 0; i < 16; i++)
        ImGui::Text(std::string("V" + to_hex<int>(i, std::hex) + "=0x" + to_hex<int>(_registers.V[i], std::hex)).c_str());
    ImGui::NewLine();
    ImGui::Text(std::string("I=0x" + to_hex<int>(_registers.I, std::hex)).c_str());
    ImGui::Text(std::string("PC=0x" + to_hex<int>(_registers.PC, std::hex)).c_str());
    ImGui::Text(std::string("SP=0x" + to_hex<int>(_registers.SP, std::hex)).c_str());
    ImGui::NewLine();
    ImGui::Text(std::string("TD=0x" + to_hex<int>(_registers.timer_delay, std::hex)).c_str());
    ImGui::Text(std::string("TS=0x" + to_hex<int>(_registers.timer_sound, std::hex)).c_str());
}