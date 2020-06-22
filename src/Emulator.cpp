/*
** EPITECH PROJECT, 2020
** CHIP-8-Emulator
** File description:
** Emulator
*/

#include "Emulator.hpp"

Emulator::Emulator(std::string gamepath, sf::RenderWindow &window, sf::Sound &sound) : _window(window), _sound(sound)
{
    std::cout << "Emulator: Starting with " << gamepath << std::endl;
    machine = std::make_shared<Opcodes>();
    this->initRegistersMemory();
    this->openFile(gamepath);
    machine->_gamepath = gamepath;
    machine->opcodes[0].masque = 0x0000; machine->opcodes[0].id = 0x0FFF;
    machine->opcodes[1].masque = 0xFFFF; machine->opcodes[1].id = 0x00E0;
    machine->opcodes[2].masque = 0xFFFF; machine->opcodes[2].id = 0x00EE;
    machine->opcodes[3].masque = 0xF000; machine->opcodes[3].id = 0x1000;
    machine->opcodes[4].masque = 0xF000; machine->opcodes[4].id = 0x2000;
    machine->opcodes[5].masque = 0xF000; machine->opcodes[5].id = 0x3000;
    machine->opcodes[6].masque = 0xF000; machine->opcodes[6].id = 0x4000;
    machine->opcodes[7].masque = 0xF00F; machine->opcodes[7].id = 0x5000;
    machine->opcodes[8].masque = 0xF000; machine->opcodes[8].id = 0x6000;
    machine->opcodes[9].masque = 0xF000; machine->opcodes[9].id = 0x7000;
    machine->opcodes[10].masque = 0xF00F; machine->opcodes[10].id = 0x8000;
    machine->opcodes[11].masque = 0xF00F; machine->opcodes[11].id = 0x8001;
    machine->opcodes[12].masque = 0xF00F; machine->opcodes[12].id = 0x8002;
    machine->opcodes[13].masque = 0xF00F; machine->opcodes[13].id = 0x8003;
    machine->opcodes[14].masque = 0xF00F; machine->opcodes[14].id = 0x8004;
    machine->opcodes[15].masque = 0xF00F; machine->opcodes[15].id = 0x8005;
    machine->opcodes[16].masque = 0xF00F; machine->opcodes[16].id = 0x8006;
    machine->opcodes[17].masque = 0xF00F; machine->opcodes[17].id = 0x8007;
    machine->opcodes[18].masque = 0xF00F; machine->opcodes[18].id = 0x800E;
    machine->opcodes[19].masque = 0xF00F; machine->opcodes[19].id = 0x9000;
    machine->opcodes[20].masque = 0xF000; machine->opcodes[20].id = 0xA000;
    machine->opcodes[21].masque = 0xF000; machine->opcodes[21].id = 0xB000;
    machine->opcodes[22].masque = 0xF000; machine->opcodes[22].id = 0xC000;
    machine->opcodes[23].masque = 0xF000; machine->opcodes[23].id = 0xD000;
    machine->opcodes[24].masque = 0xF0FF; machine->opcodes[24].id = 0xE09E;
    machine->opcodes[25].masque = 0xF0FF; machine->opcodes[25].id = 0xE0A1;
    machine->opcodes[26].masque = 0xF0FF; machine->opcodes[26].id = 0xF007;
    machine->opcodes[27].masque = 0xF0FF; machine->opcodes[27].id = 0xF00A;
    machine->opcodes[28].masque = 0xF0FF; machine->opcodes[28].id = 0xF015;
    machine->opcodes[29].masque = 0xF0FF; machine->opcodes[29].id = 0xF018;
    machine->opcodes[30].masque = 0xF0FF; machine->opcodes[30].id = 0xF01E;
    machine->opcodes[31].masque = 0xF0FF; machine->opcodes[31].id = 0xF029;
    machine->opcodes[32].masque = 0xF0FF; machine->opcodes[32].id = 0xF033;
    machine->opcodes[33].masque = 0xF0FF; machine->opcodes[33].id = 0xF055; 
    machine->opcodes[34].masque = 0xF0FF; machine->opcodes[34].id = 0xF065;
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
            machine->_memory[START_ADDRESS + i] = data[i];
	}
    else
        throw Error("Error loading .ch8 file.");
}

void Emulator::initRegistersMemory()
{
    for (int i = 0; i < 16; i++)
        machine->_registers.V[i] = 0;
    machine->_registers.I = 0;
    machine->_registers.PC = START_ADDRESS;
    machine->_registers.SP = 0;
    machine->_registers.DT = 0;
    machine->_registers.ST = 0;
    machine->_action = 0;
    machine->_opcode = 0;
    for (int i = 0; i < 4096; i++)
        machine->_memory[i] = 0;
    for (int i = 0; i < 16; i++)
        machine->_keys[i] = 0;
    for (int i = 0; i < 16; i++)
        machine->_stack[i] = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        machine->_display[i] = 1;
    for (int i = 0; i < 80; i++)
        machine->_memory[i] = this->fonts[i];
}

void Emulator::executeOperation()
{
    machine->_opcode = machine->_memory[machine->_registers.PC] << 8 | this->machine->_memory[machine->_registers.PC + 1];
    for (machine->_action = 0; machine->_action < 35; machine->_action++) { 
        if ((machine->opcodes[machine->_action].masque & machine->_opcode) == machine->opcodes[machine->_action].id)
           break; 
    }
    unsigned char b3 = (machine->_opcode & (0x0F00)) >> 8;
    unsigned char b2 = (machine->_opcode & (0x00F0)) >> 4;
    unsigned char b1 = (machine->_opcode & (0x000F));

    machine->action((Opcodes::TAction::Actions)machine->_action, b1, b2, b3);
    
    if (machine->_registers.DT > 0)
        --machine->_registers.DT;
    if (machine->_registers.ST > 0) {
        if (machine->_registers.ST == 1)
            this->_sound.play();
        --machine->_registers.ST;
    }
}

void Emulator::setKey(unsigned char key, bool state)
{
    machine->_keys[key] = state;
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
        if (machine->_display[i] == 1)
            ImGui::DrawRectFilled(rectangle, sf::Color::White);
        else if (machine->_display[i] == 0)
            ImGui::DrawRectFilled(rectangle, sf::Color::Black);
        else
            ImGui::DrawRectFilled(rectangle, sf::Color::Red);
        x++;
    }
}

void Emulator::displayDump()
{
    static MemoryEditor memory;
    memory.DrawWindow("Heap Memory Dump", this->machine->_memory, 4096);
    static MemoryEditor display;
    display.DrawWindow("Video RAM Dump", machine->_display, WIDTH * HEIGHT);
    static MemoryEditor stack;
    stack.DrawWindow("Stack Dump", machine->_stack, 16);
}