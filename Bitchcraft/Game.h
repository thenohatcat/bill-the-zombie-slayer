#ifndef BITCHCRAFT_GAME_inc
#define BITCHCRAFT_GAME_inc

//version: 0.1

#if !defined(BITCHCRAFT_V0_1r) && !defined(BITCHCRAFT_V0_1d)
#error Bitchcraft: Game.h: Incorrect Version, required: 0.1
#endif

#include <vector>
#include <SFML/Graphics.hpp>

#define DllImport   __declspec( dllimport )
#define DllExport   __declspec( dllexport )

namespace Bitchcraft
{
	class Game
	{
	public:
		DllExport Game(const char *title, int width = 640, int height = 480);
		DllExport ~Game();

		DllImport virtual void run();

		DllImport virtual void draw(float gameTime, float deltaTime) = 0;

		DllImport virtual void update(float gameTime, float deltaTime) = 0;

		DllImport virtual void damage(float h) = 0;

		DllImport virtual void score(int p) = 0;

	protected:
		sf::RenderWindow *mWind;
		sf::Clock *mClk;

		sf::Font font;

		sf::Vector2f mPos;

		float health;
		int points;

	};
}

#endif //BITCHCRAFT_GAME_inc