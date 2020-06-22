/*
** EPITECH PROJECT, 2020
** CHIP_8_Emulator
** File description:
** file
*/

#include "Application.hpp"

Application::Application(int argc, char **argv) : binary_name(std::string(argv[1]))
{
    
    if (!buffer.loadFromFile("beep.wav"))
        throw Error("Sound file parsing parsing failed!");
    sound.setBuffer(buffer);
    window.create(sf::VideoMode(1400, 600), "CHIP-8 Emulator");
    window.setFramerateLimit(60);
    srand(time(0));
    ImGui::SFML::Init(window);
    emulator = std::make_unique<Emulator>(argv[1], window, sound);
}

Application::~Application()
{
    ImGui::SFML::Shutdown();
}

void Application::Run()
{
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                can_continue = true;
        }

        sf::Time time = clock.getElapsedTime();
        double fps = 1.0 / time.asSeconds();
        clock.restart().asSeconds();

        ImGui::SFML::Update(window, deltaClock.restart());
        displayRegisters(emulator->getRegisters(), emulator->getOpcode(), emulator->getAction());

        //if (can_continue)
        emulator->executeOperation();

        emulator->setKey(0x1, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1));
        emulator->setKey(0x2, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2));
        emulator->setKey(0x3, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3));
        emulator->setKey(0xC, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4));

        emulator->setKey(0x4, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q));
        emulator->setKey(0x5, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W));
        emulator->setKey(0x6, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E));
        emulator->setKey(0xD, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R));

        emulator->setKey(0x7, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A));
        emulator->setKey(0x8, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S));
        emulator->setKey(0x9, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D));
        emulator->setKey(0xE, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F));

        emulator->setKey(0xA, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z));
        emulator->setKey(0x0, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X));
        emulator->setKey(0xB, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C));
        emulator->setKey(0xF, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V));

        window.clear();
        ImGui::Begin(binary_name.c_str());

        ImGui::Text(std::string("FPS: " + std::to_string((int)fps)).c_str());

        emulator->displayVideo();

        ImGui::End();
        emulator->displayDump();
        ImGui::SFML::Render(window);
        window.display();
        can_continue = false;
    }
}

void Application::displayRegisters(const struct registers &_registers, short opcode, size_t action)
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

std::string Application::Usage(const std::string &binary)
{
    std::string str;

    str.append("USAGE: " + binary + "game.ch8");
    return str;
}