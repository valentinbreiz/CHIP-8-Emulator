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
    sf::RenderWindow window;
    sf::Event event;
    sf::Clock deltaClock;
    std::unique_ptr<Emulator> emulator;
    sf::Clock clock;

    if (argc != 2) {
        std::cerr << "USAGE: " << argv[0] << "game.ch8" << std::endl;
        return (84);
    }

    window.create(sf::VideoMode(1400, 600), "CHIP-8 Emulator");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    emulator = std::make_unique<Emulator>(argv[1], window);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time time = clock.getElapsedTime();
        double fps = 1.0 / time.asSeconds();
        clock.restart().asSeconds();

        ImGui::SFML::Update(window, deltaClock.restart());
        displayRegisters(emulator->getRegisters(), emulator->getOpcode(), emulator->getAction());

        emulator->executeOperation();
        
        window.clear();
        ImGui::Begin(argv[1]);

        ImGui::Text(std::string("FPS: " + std::to_string((int)fps)).c_str());

        emulator->displayVideo();

        ImGui::End();
        emulator->displayDump();
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}

void displayRegisters(const struct registers &_registers, short opcode, size_t action)
{
    ImGui::Begin("Registers values");
    for (int i = 0; i < 16; i++)
        ImGui::Text(std::string("V" + to_hex<int>(i, std::hex) + "=0x" + to_hex<int>(_registers.V[i], std::hex)).c_str());
    ImGui::NewLine();
    ImGui::Text(std::string("I=0x" + to_hex<int>(_registers.I, std::hex)).c_str());
    ImGui::Text(std::string("PC=0x" + to_hex<int>(_registers.PC, std::hex)).c_str());
    ImGui::Text(std::string("SP=0x" + to_hex<int>(_registers.SP, std::hex)).c_str());
    ImGui::NewLine();
    ImGui::Text(std::string("DT=0x" + to_hex<int>(_registers.DT, std::hex)).c_str());
    ImGui::Text(std::string("ST=0x" + to_hex<int>(_registers.ST, std::hex)).c_str());
    ImGui::NewLine();
    ImGui::Text(std::string("OPCODE=0x" + to_hex<int>(opcode, std::hex)).c_str());
    ImGui::Text(std::string("Action=" + std::to_string(action)).c_str());
    ImGui::End();
}