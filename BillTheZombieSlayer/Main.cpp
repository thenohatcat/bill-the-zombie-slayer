#include <Game.h>
#include <QuadTree.h>

#include <SFML\Graphics.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include "BtZS_Game.h"

#include <list>

float x = 0;

void col(Bitchcraft::TreeNode *n)
{	
//	printf("Collide 1 %d\n", *(int*)(n->content));
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			x += 1;
}

int main(int argc, char ** argv)
{
	Bitchcraft::QuadTree t = *Bitchcraft::QuadTree::generate(1);

	clock_t begin = clock();
	for (int i = 0; i < 1000; i++)
	{
		Bitchcraft::TreeNode *n = new Bitchcraft::TreeNode(sf::Rect<float>((rand() % 18) + 1, (rand() % 18) + 1, 1, 1));
		n->content = new int*; *(int*)(n->content) = i + 1;
		t.insert(n, 0, 0, 20, 20);
	}
	clock_t end = clock();
	printf("%f\n", (double(end - begin) / CLOCKS_PER_SEC));

//	BtZS gm("GP169 \"Bill the Zombie Slayer\" v0.1a");

//	gm.run();

	Bitchcraft::TreeNode n(sf::Rect<float>(0, 0, 2, 2)); n.collide = col;

	float tm = 0;
	for (int i = 0; i < 100; i++)
	{
		begin = clock();
		for (int i = 0; i < 1000; i++)
		{
			Bitchcraft::TreeNode *n = new Bitchcraft::TreeNode(sf::Rect<float>((rand() % 18) + 1, (rand() % 18) + 1, 1, 1));
			n->content = new int*; *(int*)(n->content) = i + 1;
			t.insert(n, 0, 0, 20, 20);
		}
		for (int j = 0; j < 1000; j++)
		{
			n.bound.left = (rand() % 8) + 1;
			n.bound.top = (rand() % 8) + 1;
			Bitchcraft::QuadTree::collide(&t, &n, 0, 0, 20, 20);
			t.collide_clear();
		}
		t.clear();
		end = clock();
		tm = tm + ((double(end - begin) / CLOCKS_PER_SEC) - tm) / (i + 1);
	}
	printf("%f %f\n", 1 / tm, x);

	getchar();

	return 0;
}