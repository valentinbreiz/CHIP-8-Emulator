/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** main
*/

#include "include.hpp"
#include "Application.hpp"
#include "Error.hpp"

int main(int argc, char **argv)
{
    std::shared_ptr<Application> app;

    if (argc != 2) {
        std::cout << app->Usage(argv[0]) << std::endl;
        return (84);
    }
    try {
        app = std::make_shared<Application>(argc, argv);
        app->Run();
    } catch (const Error &e) {
        std::cout << e.what() << std::endl;
        return (84);
    }
    return (0);
}