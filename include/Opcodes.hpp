/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** Opcodes
*/

#pragma once

#include "include.hpp"

#define HEIGHT 32
#define WIDTH 64
#define PIXEL_SIZE 9
#define START_ADDRESS 0x200

struct registers
{
    unsigned char V[16]; //registers
    unsigned short I; //index register
    unsigned short PC; //program counter
    unsigned char SP; //stack pointer
    unsigned char DT; //Timer Delay
    unsigned char ST; //Timer Sound
};

struct opcode
{ 
    unsigned short masque;
    unsigned short id;
};

class Opcodes
{
    public:
        Opcodes();
        ~Opcodes();

        typedef void (Opcodes::*TArithActionFunc)(unsigned char,unsigned char,unsigned char);

        struct TAction
        {
            enum Actions
            {
                _0NNN,
                _00E0,
                _00EE,
                _1NNN,
                _2NNN,
                _3XNN,
                _4XNN,
                _5XY0,
                _6XNN,
                _7XNN,
                _8XY0,
                _8XY1,
                _8XY2,
                _BXY3,
                _8XY4,
                _8XY5,
                _8XY6,
                _8XY7,
                _8XYE,
                _9XY0,
                _ANNN,
                _BNNN,
                _CXNN,
                _DXYN,
                _EX9E,
                _EXA1,
                _FX07,
                _FX0A,
                _FX15,
                _FX18,
                _FX1E,
                _FX29,
                _FX33,
                _FX55,
                _FX65,
                count
            };
        };

        void action(TAction::Actions a_actionIdx, unsigned char b1, unsigned char b2, unsigned char b3)
        {
            (this->*m_actionFcns[a_actionIdx])(b1, b2, b3);
        }

        std::string _gamepath;
        struct registers _registers;
        unsigned char _memory[4096];
        unsigned short _stack[16];
        unsigned char _keys[16];
        unsigned char _display[WIDTH * HEIGHT];
        unsigned short _opcode;
        size_t _action;
        struct opcode opcodes[35];

    protected:
    private:
        size_t GetPointOffset(size_t x, size_t y);
        static TArithActionFunc m_actionFcns[TAction::count];
        void opcode_0NNN(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_00E0(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_00EE(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_1NNN(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_2NNN(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_3XNN(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_4XNN(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_5XY0(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_6XNN(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_7XNN(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_8XY0(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_8XY1(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_8XY2(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_BXY3(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_8XY4(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_8XY5(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_8XY6(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_8XY7(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_8XYE(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_9XY0(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_ANNN(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_BNNN(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_CXNN(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_DXYN(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_EX9E(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_EXA1(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_FX07(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_FX0A(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_FX15(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_FX18(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_FX1E(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_FX29(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_FX33(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_FX55(unsigned char b1, unsigned char b2, unsigned char b3);
        void opcode_FX65(unsigned char b1, unsigned char b2, unsigned char b3);
};