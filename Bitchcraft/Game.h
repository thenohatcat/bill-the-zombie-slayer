//version: 0.1

#ifndef BITCHCRAFT_GAME_inc
#define BITCHCRAFT_GAME_inc

#if !defined(V0_1r) && !defined(V0_1d)
#error Game.h: Incorrect Version, required: 0.1
#endif

#define DllImport   __declspec( dllimport )
#define DllExport   __declspec( dllexport )

namespace Bitchcraft
{
	class Game
	{
	public:
		DllExport Game();
	};
}

#endif //BITCHCRAFT_GAME_inc