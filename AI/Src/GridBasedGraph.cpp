#include "Precompiled.h"
#include "GridBasedGraph.h"

using namespace AI;


void GridBasedGraph::Inititalize(int colums, int rows)
{
	mNodes.clear();
	mNodes.reserve(rows * colums);

	mColums = colums;
	mRows = rows;

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < colums; ++x	)
		{
			Node& node = mNodes.emplace_back();
			node.colum = x;
			node.row = y;
		}
	}
}
void GridBasedGraph::ResetSearchParams()
{
	for (Node& node : mNodes)
	{
		node.Reset();
	}
}

GridBasedGraph::Node* GridBasedGraph:: getNode(int x, int y)
{

	const int index = getIndex(x,y);

	if (index >= 0 && index < mNodes.size())
	{
		return &mNodes[index];
	}
	
	return nullptr;
}
const GridBasedGraph::Node* GridBasedGraph::getNode(int x, int y)const
{
	const int index = getIndex(x, y);

	if (index >= 0 && index < mNodes.size())
	{
		return &mNodes[index];
	}

	return nullptr;
}

int GridBasedGraph::getIndex(int x, int y)const
{
	return x + (y * mColums);
}