/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** Opcodes
*/

#ifndef OPCODES_HPP_
#define OPCODES_HPP_

#include "Emulator.hpp"

class Opcodes
{
    public:
        Opcodes(std::shared_ptr<Emulator> emulator);
        ~Opcodes();

        typedef void (Opcodes::*TArithActionFunc)();

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

        int action(TAction::Actions a_actionIdx)
        {
            (this->*m_actionFcns[a_actionIdx])();
        }

    protected:
    private:

        std::shared_ptr<Emulator> _emulator;

        static TArithActionFunc m_actionFcns[TAction::count];

        void opcode_0NNN();
        void opcode_00E0();
        void opcode_00EE();
        //todo add other opcodes
};

#endif /* !OPCODES_HPP_ */