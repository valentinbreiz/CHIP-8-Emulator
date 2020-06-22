/*
** EPITECH PROJECT, 2020
** CHIP_8_Emulator
** File description:
** file
*/

#ifndef CHIP_8_EMULATOR_ERROR_HPP
#define CHIP_8_EMULATOR_ERROR_HPP

#include <exception>
#include <string>

class Error : public std::exception
{
    public:
        Error(const char *msg) : _msg(msg) {};
        Error(const std::string &msg) : _msg(msg.c_str()) {};
        const char *what() const throw () { return (_msg); }
    private:
        const char *_msg;
};

#endif //CHIP_8_EMULATOR_ERROR_HPP
