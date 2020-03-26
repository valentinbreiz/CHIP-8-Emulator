/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** Emulator
*/

#include "Emulator.hpp"

Emulator::Emulator(std::string gamepath, sf::RenderWindow &window, sf::Sound &sound)
: _gamepath(gamepath),
_window(window),
_sound(sound)
{
    std::cout << "Emulator: Starting with " << this->_gamepath << std::endl;
    this->initRegistersMemory();
    this->openFile(gamepath);
    opcodes[0].masque = 0x0000; opcodes[0].id = 0x0FFF;
    opcodes[1].masque = 0xFFFF; opcodes[1].id = 0x00E0;
    opcodes[2].masque = 0xFFFF; opcodes[2].id = 0x00EE;
    opcodes[3].masque = 0xF000; opcodes[3].id = 0x1000;
    opcodes[4].masque = 0xF000; opcodes[4].id = 0x2000;
    opcodes[5].masque = 0xF000; opcodes[5].id = 0x3000;
    opcodes[6].masque = 0xF000; opcodes[6].id = 0x4000;
    opcodes[7].masque = 0xF00F; opcodes[7].id = 0x5000;
    opcodes[8].masque = 0xF000; opcodes[8].id = 0x6000;
    opcodes[9].masque = 0xF000; opcodes[9].id = 0x7000;
    opcodes[10].masque = 0xF00F; opcodes[10].id = 0x8000;
    opcodes[11].masque = 0xF00F; opcodes[11].id = 0x8001;
    opcodes[12].masque = 0xF00F; opcodes[12].id = 0x8002;
    opcodes[13].masque = 0xF00F; opcodes[13].id = 0x8003;
    opcodes[14].masque = 0xF00F; opcodes[14].id = 0x8004;
    opcodes[15].masque = 0xF00F; opcodes[15].id = 0x8005;
    opcodes[16].masque = 0xF00F; opcodes[16].id = 0x8006;
    opcodes[17].masque = 0xF00F; opcodes[17].id = 0x8007;
    opcodes[18].masque = 0xF00F; opcodes[18].id = 0x800E;
    opcodes[19].masque = 0xF00F; opcodes[19].id = 0x9000;
    opcodes[20].masque = 0xF000; opcodes[20].id = 0xA000;
    opcodes[21].masque = 0xF000; opcodes[21].id = 0xB000;
    opcodes[22].masque = 0xF000; opcodes[22].id = 0xC000;
    opcodes[23].masque = 0xF000; opcodes[23].id = 0xD000;
    opcodes[24].masque = 0xF0FF; opcodes[24].id = 0xE09E;
    opcodes[25].masque = 0xF0FF; opcodes[25].id = 0xE0A1;
    opcodes[26].masque = 0xF0FF; opcodes[26].id = 0xF007;
    opcodes[27].masque = 0xF0FF; opcodes[27].id = 0xF00A;
    opcodes[28].masque = 0xF0FF; opcodes[28].id = 0xF015;
    opcodes[29].masque = 0xF0FF; opcodes[29].id = 0xF018;
    opcodes[30].masque = 0xF0FF; opcodes[30].id = 0xF01E;
    opcodes[31].masque = 0xF0FF; opcodes[31].id = 0xF029;
    opcodes[32].masque = 0xF0FF; opcodes[32].id = 0xF033;
    opcodes[33].masque = 0xF0FF; opcodes[33].id = 0xF055; 
    opcodes[34].masque = 0xF0FF; opcodes[34].id = 0xF065;
}

Emulator::~Emulator()
{
    std::cout << "Emulator: Ending" << std::endl;
}

void Emulator::openFile(std::string gamepath)
{
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
		data[size] = '\0';
        for (int i = 0; i < size; i++)
            _memory[START_ADDRESS + i] = data[i];
	}
    else {
        std::cerr << "Error loading file." << std::endl;
        exit(84);
    }
}

void Emulator::initRegistersMemory()
{
    for (int i = 0; i < 16; i++)
        this->_registers.V[i] = 0;
    this->_registers.I = 0;
    this->_registers.PC = START_ADDRESS;
    this->_registers.SP = 0;
    this->_registers.DT = 0;
    this->_registers.ST = 0;
    this->_action = 0;
    this->_opcode = 0;
    for (int i = 0; i < 4096; i++)
        _memory[i] = 0;
    for (int i = 0; i < 16; i++)
        _stack[i] = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        _display[i] = 1;
    for (int i = 0; i < 80; i++)
        _memory[i] = this->fonts[i];
}

void Emulator::executeOperation()
{
    this->_opcode = this->_memory[this->_registers.PC] << 8 | this->_memory[this->_registers.PC + 1];
    for (this->_action = 0; this->_action < 35; this->_action++) { 
        if ((opcodes[this->_action].masque & this->_opcode) == opcodes[this->_action].id)
           break; 
    }
    unsigned char b3 = (this->_opcode & (0x0F00)) >> 8;
    unsigned char b2 = (this->_opcode & (0x00F0)) >> 4;
    unsigned char b1 = (this->_opcode & (0x000F));
    switch (this->_action)
    {
        case _0NNN:
            break;
        case _00E0:
            for (int i = 0; i < HEIGHT * WIDTH; i++)
                this->_display[i] = 0;
            this->_registers.PC += 2;
            break;
        case _00EE:
            if (this->_registers.SP > 0) {
                this->_registers.SP--;
                this->_registers.PC = this->_stack[this->_registers.SP];
                this->_registers.PC += 2;
            }
            break;
        case _1NNN:
            this->_registers.PC = (b3 << 8) + (b2 << 4) + b1;
            break;
        case _2NNN:
            this->_stack[this->_registers.SP] = this->_registers.PC;
            if (this->_registers.SP < 15)
                this->_registers.SP++;
            this->_registers.PC = (b3 << 8) + (b2 << 4) + b1;
            break;
        case _3XNN:
            if (this->_registers.V[b3] == ((b2 << 4) + b1))
                this->_registers.PC += 4;
            else
                this->_registers.PC += 2;
            break;
        case _4XNN:
            if (this->_registers.V[b3] == ((b2 << 4) + b1))
                this->_registers.PC += 2;
            else
                this->_registers.PC += 4;
            break;
        case _5XY0:
            break;
        case _6XNN:
            this->_registers.V[b3] = (b2 << 4) + b1;
            this->_registers.PC += 2;
            break;
        case _7XNN:
            this->_registers.V[b3] += + (b2 << 4) + b1;
            this->_registers.PC += 2;
            break;
        case _8XY0:
            this->_registers.V[b3] = this->_registers.V[b2];
            this->_registers.PC += 2;
            break;
        case _8XY1:
            break;
        case _8XY2:
            this->_registers.V[b3] &= this->_registers.V[b2];
            this->_registers.PC += 2;
            break;
        case _BXY3:
            break;
        case _8XY4:
            this->_registers.V[b3] += this->_registers.V[b2];
            if (this->_registers.V[b2] > (0xFF - this->_registers.V[b3]))
                this->_registers.V[0xF] = 1;
            else
                this->_registers.V[0xF] = 0;
            this->_registers.PC += 2;
            break;
        case _8XY5:
            this->_registers.V[b3] -= this->_registers.V[b2];
            if (this->_registers.V[b2] < (this->_registers.V[b3]))
                this->_registers.V[0xF] = 1;
            else
                this->_registers.V[0xF] = 0;
            this->_registers.PC += 2;
            break;
        case _8XY6:
            break;
        case _8XY7:
            break;
        case _8XYE:
            break;
        case _9XY0:
            break;
        case _ANNN:
            this->_registers.I = (b3 << 8) + (b2 << 4) + b1;
            this->_registers.PC += 2;
            break;
        case _BNNN:
            break;
        case _CXNN:
            this->_registers.V[b3] = ((rand() % 0xFF) & ((b2 << 4) + b1));
            this->_registers.PC += 2;
            break;
        case _DXYN:
            this->_registers.V[0x0F] = 0;
            unsigned short pixel;
            for (unsigned char k = 0; k < b1; ++k){
                pixel = this->_memory[this->_registers.I + k];
                for (unsigned char j = 0; j < 8; ++j) {
                    int x = (this->_registers.V[b3] + j) % WIDTH;
                    int y = (this->_registers.V[b2] + k) % HEIGHT;
                    if ((pixel & (0x80 >> j)) != 0) {
                        if (this->_display[GetPointOffset(x, y)] == 0) {
                            this->_registers.V[0xF] = 1;
                            this->_display[GetPointOffset(x, y)] = 1;
                        }
                        else {
                            this->_display[GetPointOffset(x, y)] = 0;
                            //this->_registers.V[0xF] = 1;
                        }
                    }
                }
            }
            this->_registers.PC += 2;
            break;
        case _EX9E:
            break;
        case _EXA1:
            if (!this->_keys[this->_registers.V[b3]])
                this->_registers.PC += 4;
            else
                this->_registers.PC += 2;
            break;
        case _FX07:
            this->_registers.V[b3] = this->_registers.DT;
            this->_registers.PC += 2;
            break;
        case _FX0A:
            break;
        case _FX15:
            this->_registers.DT = this->_registers.V[b3];
            this->_registers.PC += 2;
            break;
        case _FX18:
            this->_registers.ST = this->_registers.V[b3];
            this->_registers.PC += 2;
            break;
        case _FX1E:
            break;
        case _FX29:
            this->_registers.I = this->_registers.V[b3] * 0x05;
            this->_registers.PC += 2;
            break;
        case _FX33:
            this->_memory[this->_registers.I] = this->_registers.V[b3] / 100;
            this->_memory[this->_registers.I + 1] = (this->_registers.V[b3] / 10) % 10;
            this->_memory[this->_registers.I + 1] = (this->_registers.V[b3] % 10) % 10;
            this->_registers.PC += 2;
            break;
        case _FX55:
            break;
        case _FX65:
            for (int i = this->_registers.I; i < b3; i++)
                this->_registers.V[i] = this->_memory[this->_registers.I + i];
            this->_registers.PC += 2;
            break;
        default:
            std::cout << "Unknown opcode: action=" << std::to_string(this->_action) << std::endl;
            break;
    }
    if (this->_registers.DT > 0)
        --this->_registers.DT;
    if (this->_registers.ST > 0) {
        if (this->_registers.ST == 1)
            _sound.play();
        --this->_registers.ST;
    }
}

size_t Emulator::GetPointOffset(size_t x, size_t y)
{
    return ((y * WIDTH) + x);
}

void Emulator::setKey(unsigned char key, bool state)
{
    this->_keys[key] = state;
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