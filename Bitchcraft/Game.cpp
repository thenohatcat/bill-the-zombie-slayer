#if !defined(BITCHCRAFT_V0_1r) && !defined(BITCHCRAFT_V0_1d)
#error Bitchcraft: Game.h: Incorrect Version, required: 0.1
#endif

#include "Game.h"

#include <iostream>

Bitchcraft::Game::Game()
{
	std::cout << "Test" << std::endl;
}