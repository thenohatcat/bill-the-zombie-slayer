//version: 0.1

#ifndef BITCHCRAFT_GAME_inc
#define BITCHCRAFT_GAME_inc

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

		DllExport void run();

		DllExport void draw(float gameTime, float deltaTime);

		DllExport void update(float gameTime, float deltaTime);

		DllExport void damage();

		DllExport void score();
	private:
		sf::RenderWindow *mWind;
		sf::Clock *mClk;

		sf::Vector2f mPos;

		sf::Vector2f tPos;

		float crot;

		struct projp;

		typedef struct projp
		{
			sf::Vector2f pos;
			float age;
			sf::Vector2f vel;

			static projp create(float x, float y, float vx, float vy)
			{
				projp p;
				p.pos.x = x;
				p.pos.y = y;
				p.age = 0;
				p.vel.x = vx;
				p.vel.y = vy;
				return p;
			}
		} proj;

		std::vector<sf::Vector2f> en;
		std::vector<proj> pr;

		sf::Font font;

		float health;
		int points;
	};
}

#endif //BITCHCRAFT_GAME_inc