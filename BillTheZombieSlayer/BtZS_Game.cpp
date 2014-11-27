#include <Game.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include "BtZS_Game.h"

void BtZS::run()
{
	tPos = sf::Vector2f(320, 240);
	Bitchcraft::Game::run();
}

float fps;
float otf = 0;

void BtZS::draw(float gameTime, float deltaTime)
{
	if (health > 0)
	{
		sf::CircleShape c(5);
		c.setFillColor(sf::Color::Red);
		c.setOutlineColor(sf::Color::Red);
		c.setOutlineThickness(1);

		sf::Transform tc;
		tc.translate(tPos.x - 5, tPos.y - 5);
		tc.translate(5, 5);
		tc.rotate(crot - 45, 0, 0);

		sf::CircleShape c2(10);
		c2.setFillColor(sf::Color::Blue);
		c2.setOutlineColor(sf::Color::Green);
		c2.setOutlineThickness(1);

		sf::Transform tc2;
		tc2.translate(tPos.x - 10, tPos.y - 10);

		sf::CircleShape c3(5);
		c3.setFillColor(sf::Color::White);
		c3.setOutlineColor(sf::Color::White);
		c3.setOutlineThickness(1);

		sf::Transform tc3;
		tc3.translate(mPos.x - 5, mPos.y - 5);

		mWind->draw(c3, tc3);
		mWind->draw(c2, tc2);
		mWind->draw(c, tc);

		for (std::vector<sf::Vector2f>::iterator i = en.begin(); i != en.end(); i++)
		{
			sf::CircleShape c3(5);
			c3.setFillColor(sf::Color::Red);
			c3.setOutlineColor(sf::Color::White);
			c3.setOutlineThickness(1);

			sf::Transform tc3;
			tc3.translate((*i).x - 5, (*i).y - 5);

			mWind->draw(c3, tc3);
		}

		for (std::vector<proj>::iterator i = pr.begin(); i != pr.end(); i++)
		{
			sf::CircleShape c3(2.5);
			c3.setFillColor(sf::Color::Red);
			c3.setOutlineColor(sf::Color::White);
			c3.setOutlineThickness(1);

			sf::Transform tc3;
			tc3.translate((*i).pos.x - 2.5, (*i).pos.y - 2.5);

			mWind->draw(c3, tc3);
		}

		for (std::vector<drop>::iterator i = dr.begin(); i != dr.end(); i++)
		{
			sf::Transform t;
			t.translate((*i).pos.x - 2.5, (*i).pos.y - 2.5);
			t.rotate((*i).age * 45, 0, 0);

			sf::RectangleShape r0(sf::Vector2f(20, 20));
			r0.setFillColor(sf::Color::White);
			r0.setOutlineColor(sf::Color::Blue);
			r0.setOutlineThickness(2);

			sf::Transform tr0(t);
			tr0.translate(-10, -10);

			mWind->draw(r0, tr0);

			sf::RectangleShape r1(sf::Vector2f(5, 15));
			r1.setFillColor(sf::Color::Red);
			r1.setOutlineThickness(0);

			sf::Transform tr1(t);
			tr1.translate(-2.5, -7.5);

			mWind->draw(r1, tr1);

			sf::RectangleShape r2(sf::Vector2f(15, 5));
			r2.setFillColor(sf::Color::Red);
			r2.setOutlineThickness(0);

			sf::Transform tr2(t);
			tr2.translate(-7.5, -2.5);

			mWind->draw(r2, tr2);
		}

		sf::RectangleShape r(sf::Vector2f(100, 26));
		r.setFillColor(sf::Color::White);
		r.setOutlineColor(sf::Color::Red);
		r.setOutlineThickness(2);

		sf::Transform rt;
	
		mWind->draw(r, rt);

		char tmp[16];
		sprintf(tmp, "Score: %06d", points % 1000000);
		// Create a text
		sf::Text text0(tmp, font);
		text0.setCharacterSize(12);
		text0.setStyle(sf::Text::Bold);
		text0.setColor(sf::Color::Red);
		// Draw it
		sf::Transform t0;
		mWind->draw(text0, t0);

		sprintf(tmp, "Helth: %3.0f%%", health);
		// Create a text
		sf::Text text1(tmp, font);
		text1.setCharacterSize(12);
		text1.setStyle(sf::Text::Bold);
		text1.setColor(sf::Color::Red);
		// Draw it
		sf::Transform t1;
		t1.translate(0, 12);
		mWind->draw(text1, t1);
	}
	else
	{
		// Create a text
		sf::Text text0("Game Over!", font);
		text0.setCharacterSize(20);
		text0.setStyle(sf::Text::Bold);
		text0.setColor(sf::Color::Red);
		// Draw it
		sf::Transform t0;
		t0.translate(
			320 - text0.getLocalBounds().width / 2, 
			240 - text0.getLocalBounds().height);
		mWind->draw(text0, t0);

		char tmp[16];
		sprintf(tmp, "Score: %06d", points % 1000000);
		// Create a text
		sf::Text text1(tmp, font);
		text1.setCharacterSize(12);
		text1.setStyle(sf::Text::Bold);
		text1.setColor(sf::Color::Red);
		// Draw it
		sf::Transform t1;
		t1.translate(
			320 - text1.getLocalBounds().width / 2, 
			240 + text1.getLocalBounds().height);
		mWind->draw(text1, t1);
	}

	if ((gameTime - otf) > 0.1)
	{
		fps = 1 / (deltaTime == 0 ? 1 : deltaTime);
		otf = gameTime;
	}

	char tmp[32];
	sprintf(tmp, "fps: %04.0f v0.1.0a\n", fps);

	sf::Text text1(tmp, font);
	text1.setCharacterSize(12);
	text1.setStyle(sf::Text::Bold);
	text1.setColor(sf::Color::Red);
	// Draw it
	sf::Transform t1;
	t1.translate(
		640 - text1.getLocalBounds().width, 
		480 - text1.getLocalBounds().height);
	mWind->draw(text1, t1);
}

float otp = 0;
float otd = 0;
float ote = 0;

float otdm = 0;

void BtZS::update(float gameTime, float deltaTime)
{
	if (health > 0)
	{
		crot = atan2f(mPos.y - tPos.y, mPos.x - tPos.x) * 180 / (M_PI);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			tPos.x -= 60 * deltaTime;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			tPos.x += 60 * deltaTime;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			tPos.y -= 60 * deltaTime;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			tPos.y += 60 * deltaTime;

		if (tPos.x > 620)
			tPos.x = 620;
		else if (tPos.x < 20)
			tPos.x = 20;

		if (tPos.y > 460)
			tPos.y = 460;
		else if (tPos.y < 20)
			tPos.y = 20;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if ((gameTime - otp) > 0.25)
			{
				pr.push_back(proj::create(tPos.x, tPos.y, 120 * cos(crot * M_PI / 180), 120 * sin(crot * M_PI / 180)));
				otp = gameTime;
			}
		}

		for (std::vector<sf::Vector2f>::iterator i = en.begin(); i != en.end();)
		{
			float dist = sqrtf(powf((*i).x - tPos.x, 2) + powf((*i).y - tPos.y, 2));
//			printf("%f\n", dist);
			if (dist < 15)
			{
//				i = en.erase(i);
				if ((gameTime - otdm) > 0.5)
				{
					damage(-5.0);
					otdm = gameTime;
				}
				i++;
			}
			else
			{	
				float dir = atan2f((*i).y - tPos.y, (*i).x - tPos.x);
				(*i).x += cos(dir) * -50 * deltaTime;
				(*i).y += sin(dir) * -50 * deltaTime;
				i++;
			}
		}

		for (std::vector<proj>::iterator i = pr.begin(); i != pr.end();)
		{
			if ((*i).age > 4 || (*i).pos.x < 0 || (*i).pos.x > 640 || (*i).pos.y < 0 || (*i).pos.y > 480)
			{
				i = pr.erase(i);
			}
			else
			{
				bool er = false;
				for (std::vector<sf::Vector2f>::iterator j = en.begin(); j != en.end();)
				{
					float dist = sqrtf(powf((*i).pos.x - (*j).x, 2) + powf((*i).pos.y - (*j).y, 2));
					if (dist < 10)
					{
						er = true;
						score(10);
						j = en.erase(j);
					}
					else
						j++;
				}
				if (er)
					i = pr.erase(i);
				else
				{
					(*i).age += deltaTime;
					(*i).pos.x += (*i).vel.x * deltaTime;
					(*i).pos.y += (*i).vel.y * deltaTime;
					i++;
				}
			}
		}

		for (std::vector<drop>::iterator i = dr.begin(); i != dr.end();)
		{
			if ((*i).age > 60)
			{
				i = dr.erase(i);
			}
			else
			{
				float dist = sqrtf(powf((*i).pos.x - tPos.x, 2) + powf((*i).pos.y - tPos.y, 2));
				if (dist < 30)
				{
					i = dr.erase(i);
					damage(10.0);
				}
				else
				{
					(*i).age += deltaTime;
					i++;
				}
			}
		}

		if ((gameTime - otd) > 5)
		{
			if ((rand() % 1000) >= 999 && dr.size() < 100)
			{
				dr.push_back(drop::create((rand() % 600) + 20, (rand() % 440) + 20));
				otd = gameTime;
			}
		}

		if ((gameTime - ote) > 0.5)
		{
			if ((rand() % 1000) >= 999 && en.size() < 100)
			{
				int r = rand() % 4;
				sf::Vector2f pos;
				if (r == 0)
				{
					pos.x = 0;
					pos.y = rand() % 480;
				}
				else if (r == 1)
				{
					pos.x = rand() % 640;
					pos.y = 0;
				}
				else if (r == 2)
				{
					pos.x = 640;
					pos.y = rand() % 480;
				}
				else if (r == 3)
				{
					pos.x = rand() % 640;
					pos.y = 480;
				}
				en.push_back(pos);
				ote = gameTime;
			}
		}
	}
}

void BtZS::damage(float h)
{
	health += h;
	if (health < 0)
		health = 0;
	else if (health > 100)
		health = 100;
}

void BtZS::score(int p)
{
	points += p;
}