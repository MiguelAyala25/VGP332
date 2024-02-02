#pragma once
#include <array>
#include <vector>


namespace AI
{
	class GridBasedGraph
	{
	public:
		enum Directions
		{
			North,
			South,
			East,
			West,
			NorthEast,
			NorthWest,
			SouthEast,
			SouthWest
		};

		struct Node
		{
			//node info
			int colum = 0;
			int row = 0;			
			std::array<Node*, 8> neighbours;

			// pathing info
			Node* parent = nullptr;
			bool opened = false;
			bool closed = false;
			float cost = 0.0f;
			float heuristic = 0.0f;

			void Reset()
			{
				parent = nullptr;
				opened = false;
				closed = false;
				cost = 0.0f;
				heuristic = 0.0f;
			}

		};

		void Inititalize(int colums, int rows);
		void ResetSearchParams();

		Node* getNode(int x, int y);
		const Node* getNode(int x, int y)const;

		int getColums() const { return mColums; }
		int getRows() const { return mRows; }

	private:

		int getIndex(int x, int y)const;

		int mColums = 0;
		int mRows = 0;

		std::vector <Node> mNodes;

	};
	using NodeList = std::list<GridBasedGraph::Node*>;
}