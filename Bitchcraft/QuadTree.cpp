#include "QuadTree.h"
#include <list>

Bitchcraft::QuadTree::QuadTree(QuadTree *p, QuadTree *ur, QuadTree *ul, QuadTree *ll, QuadTree *lr)
	: parent(p), subTree0(ur), subTree1(ul), subTree2(ll), subTree3(lr)
{ }

Bitchcraft::QuadTree* Bitchcraft::QuadTree::generate(int levels)
{
	if (levels > 0)
	{
		QuadTree *t = new QuadTree(NULL, generate(levels - 1), generate(levels - 1), generate(levels - 1), generate(levels - 1));
		t->subTree0->parent = t;
		t->subTree1->parent = t;
		t->subTree2->parent = t;
		t->subTree3->parent = t;
		return t;
	}
	else
	{
		return new QuadTree(NULL, NULL, NULL, NULL, NULL);
	}
}

void Bitchcraft::QuadTree::insert(TreeNode *n, float x, float y, float w, float h)
{
	if (subTree0 == NULL)
		nodes.push_back(n);
	else
	{
		if (n->bound.intersects(sf::Rect<float>(x + w / 2,	y,			w / 2,	h / 2)))
			subTree0->insert(n, x + w / 2,	y,			w / 2,	h / 2);
		if (n->bound.intersects(sf::Rect<float>(x,			y,			w / 2,	h / 2)))
			subTree1->insert(n, x,			y,			w / 2,	h / 2);
		if (n->bound.intersects(sf::Rect<float>(x,			y + h / 2,			w / 2,	h / 2)))
			subTree2->insert(n, x,			y + h / 2,	w / 2,	h / 2);
		if (n->bound.intersects(sf::Rect<float>(x + w / 2,	y + h / 2,	w / 2,	h / 2)))
			subTree3->insert(n, x + w / 2,	y + w / 2,	w / 2,	h / 2);
	}
}

void Bitchcraft::QuadTree::collide(QuadTree *t, TreeNode *n, float x, float y, float w, float h)
{
	if (t->subTree0 == NULL) //Is leaf
		for (std::list<TreeNode*>::iterator i = t->nodes.begin(); i != t->nodes.end(); i++)
		{
			if (!(*i)->visited)
				if (n->bound.intersects((*i)->bound))
				{
					n->collide(*i);
					(*i)->visited = true;
				}
		}
	else
	{
		if (n->bound.intersects(sf::Rect<float>(x + w / 2,	y,			w / 2,	h / 2)))
			collide(t->subTree0, n, x + w / 2,	y,			w / 2,	h / 2);
		if (n->bound.intersects(sf::Rect<float>(x,			y,			w / 2,	h / 2)))
			collide(t->subTree1, n, x,			y,			w / 2,	h / 2);
		if (n->bound.intersects(sf::Rect<float>(x,			y + h / 2,	w / 2,	h / 2)))
			collide(t->subTree2, n, x,			y + h / 2,	w / 2,	h / 2);
		if (n->bound.intersects(sf::Rect<float>(x + w / 2,	y + h / 2,	w / 2,	h / 2)))
			collide(t->subTree3, n, x + w / 2,	y + h / 2,	w / 2,	h / 2);
	}
}

void Bitchcraft::QuadTree::clear()
{
	if (subTree0 == NULL) //Is Leaf
		nodes.clear();
	else
	{
		subTree0->clear();
		subTree1->clear();
		subTree2->clear();
		subTree3->clear();
	}
}

void Bitchcraft::QuadTree::collide_clear()
{
	if (subTree0 == NULL) //Is Leaf
		for (std::list<TreeNode*>::iterator i = nodes.begin(); i != nodes.end(); i++)
		{
			(*i)->visited = false;
		}
	else
	{
		subTree0->collide_clear();
		subTree1->collide_clear();
		subTree2->collide_clear();
		subTree3->collide_clear();
	}
}

Bitchcraft::TreeNode::TreeNode(sf::Rect<float> b)
	:	bound(b), visited(false)
{ }