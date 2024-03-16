#pragma once

#include "GridBasedGraph.h"
#include <XEngine.h>
#include <AI.h>

using Path = std::vector<X::Math::Vector2>;
namespace AI
{
	using GetCost = std::function<float(const GridBasedGraph::Node*, const GridBasedGraph::Node*)>;
	using GetHeuristic = std::function<float(const GridBasedGraph::Node*, const GridBasedGraph::Node*)>;

	class AStar
	{
	public:

		bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost, GetHeuristic getHeuristic);

		const NodeList& GetClosedList() const { return mClosedList; }

		Path ReconstructPath(GridBasedGraph::Node* endNode);

	private:
		NodeList mOpenList;
		NodeList mClosedList;

		//grid to world
		X::Math::Vector2 GridToWorld(int gridX, int gridY) const {
			const int tileSize = 32;
			float worldX = gridX * tileSize + tileSize / 2.0f;
			float worldY = gridY * tileSize + tileSize / 2.0f;
			return X::Math::Vector2{ worldX, worldY };
		}
	};
}