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
	//for (int i = 0; i < 200000; i++)
	//	for (int j = 0; j < 10000; j++)
	//		for (int k = 0; k < 10000; k++)
	//			x = sqrt(pow(n->bound.left - j, 2) + pow(n->bound.top - k, 2));
}

int main(int argc, char ** argv)
{
	int w = 640, h = 480;

	printf("1000 x 500;0;1;2;3\n");
	for (int m = 1; m <= 20; m++)
	{
		std::vector<Bitchcraft::TreeNode*> nds;
		for (int k = 1; k < 6;k++)
			for (int i = 0; i < 1000; i++)
			{
				Bitchcraft::TreeNode *n = new Bitchcraft::TreeNode(sf::Rect<float>((rand() % w), (rand() % h), 5 * k, 5 * k));
				n->content = new int*; *(int*)(n->content) = k * 100 + i + 1;
				nds.push_back(n);
			}

		printf("%d * %d", 5 * m, 5 * m);
			
		Bitchcraft::TreeNode n(sf::Rect<float>(0, 0, 5 * m, 5 * m)); n.collide = col;

		for (int l = 0; l < 4; l++)
		{
			Bitchcraft::QuadTree *t = Bitchcraft::QuadTree::generate(l);

			float tm0 = 0;
			float tm1 = 0;
			for (int k = 0; k < 3; k++)
			{
				for (int i = 0; i < 100; i++)
				{
					clock_t begin = clock();
					for (int i = 0; i < 1000 * 5; i++)
					{
						t->insert(nds.at(i), 0, 0, w, h);
					}
					clock_t end = clock();
					begin = clock();
					tm0 = tm0 + ((double(end - begin) / CLOCKS_PER_SEC) - tm0) / ((k * 100) + i + 1);
					for (int j = 0; j < 500; j++)
					{
						n.bound.left = (rand() % w) + 1;
						n.bound.top = (rand() % h) + 1;
						Bitchcraft::QuadTree::collide(t, &n, 0, 0, w, h);
						t->collide_clear();
					}
					end = clock();
					tm1 = tm1 + ((double(end - begin) / CLOCKS_PER_SEC) - tm1) / ((k * 100) + i + 1);
					t->clear();
				}
			}
			printf(";%f", tm1 + tm0);

			delete t;
		}
		printf("\n");

//		for (int i = 0; i < nds.size(); i++)
//			delete nds.at(i);
		nds.clear();
	}

	getchar();

	return 0;
}