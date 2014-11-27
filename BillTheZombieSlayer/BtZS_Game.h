#ifndef BtZS_BtZS_GAME_inc
#define BtZS_BtZS_GAME_inc

#include <Game.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

class BtZS
	:	public Bitchcraft::Game
{
public:
	BtZS(const char *title, int width = 640, int height = 480)
		: Bitchcraft::Game(title, width, height)
	{ }

	virtual void run();

	virtual void draw(float gameTime, float deltaTime);

	virtual void update(float gameTime, float deltaTime);

	virtual void damage(float h);

	virtual void score(int p);
private:
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

	struct dropp;

	typedef struct dropp
	{
		sf::Vector2f pos;
		float age;

		static dropp create(float x, float y)
		{
			dropp d;
			d.pos.x = x;
			d.pos.y = y;
			d.age = 0;
			return d;
		}
	} drop;

	sf::Vector2f tPos;

	float crot;

	std::vector<sf::Vector2f> en;
	std::vector<proj> pr;
	std::vector<drop> dr;
};

#endif //BtZS_BtZS_GAME_inc