/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** main
*/

#include "Emulator.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

#define SCREEN_X 64
#define SCREEN_Y 32

int main(int argc, char **argv)
{
    std::string title;
    sf::RenderWindow window;
    sf::Event event;
    std::unique_ptr<Emulator> emulator;

    if (argc != 2) {
        std::cerr << "USAGE: " << argv[0] << "game.ch8" << std::endl;
        return (84);
    }
    title = "CHIP-8 Emulator : " + std::string(argv[1]);
    window.create(sf::VideoMode(SCREEN_X * 10, SCREEN_Y * 10), title);
    emulator = std::make_unique<Emulator>(argv[1]);
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.display();
    }
    return 0;
}