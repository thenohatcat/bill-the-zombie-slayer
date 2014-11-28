#ifndef BITCHCRAFT_QUADTREE_inc
#define BITCHCRAFT_QUADTREE_inc

#include <list>
#include <SFML/Graphics.hpp>

#define DllImport   __declspec( dllimport )
#define DllExport   __declspec( dllexport )

namespace Bitchcraft
{
	class TreeNode;

	class QuadTree
	{
	public:
		DllExport QuadTree(QuadTree *parent, QuadTree *ur, QuadTree *ul, QuadTree *ll, QuadTree *lr);

		DllExport static QuadTree* generate(int levels);

		DllExport static void collide(QuadTree *t, TreeNode *n, float x, float y, float w, float h);

		DllExport void collide_clear();

		DllExport void insert(TreeNode *n, float x, float y, float w, float h);

		DllExport void clear();

	private:
		QuadTree *parent;
		QuadTree *subTree0; //UpperRight
		QuadTree *subTree1; //UpperLeft
		QuadTree *subTree2; //LowerLeft
		QuadTree *subTree3; //LowerRight

		std::list<TreeNode*> nodes;
	};

	class TreeNode
	{
	public:
		DllExport TreeNode(sf::Rect<float> b);

		void (*collide)(TreeNode *n);

		void *content;

//		DllImport virtual void collide(TreeNode *n);

		sf::Rect<float> bound;

		bool visited;
	};
}

#endif //BITCHCRAFT_QUADTREE_inc