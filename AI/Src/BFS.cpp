#include "Precompiled.h"
#include "BFS.h"

using namespace AI;

 bool BFS::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY)
{
	bool found = false;

	graph.ResetSearchParams();

	mOpenList.clear();
	mClosedList.clear();

	//add the start node to the open list

	GridBasedGraph::Node* node = graph.getNode(startX, startY);
	node->opened = true;
	mOpenList.push_back(node);

	//do the search
	while (!found && !mOpenList.empty())
	{
		//bfs First in first out
		node = mOpenList.front();
		mOpenList.pop_front();


		if (node->colum == endX && node->row == endY)
		{
			found == true;
		}
		else
		{
			for (GridBasedGraph::Node* neighbor : node->neighbours)
			{
				if (neighbor == nullptr || neighbor->opened)
				{
					continue;
				}
				mOpenList.push_back(neighbor);
				neighbor->opened = true;
				neighbor->parent = node;
			}
		}

		//add to closed list
		mClosedList.push_back(node);
		node->closed = true;

	}



	return found;
}