#pragma once

#include <XEngine.h>
#include <AI.h>
#include "GridBasedGraph.h"


using Path = std::vector<X::Math::Vector2>;

struct Tile
{
	X::TextureId textureId;
	bool isWalkable = false;
};


class TileMap
{
public:
	void LoadTiles(const char* fileName);
	void LoadMap(const char* fileName);

	void Render(bool debug) const;

	bool IsBaseTile(int x, int y) const;
	bool IsCommonTile(int x, int y) const;

	bool IsBlocked(int x, int y) const;
	int getColumns() const { return mColumns; }
	int getRows() const { return mRows; }


	X::Math::Vector2 GetPixelPosition(int x, int y)const;

	Path FindPathBFS(int startX, int startY, int endX, int endY);
	Path FindPathDFS(int startX, int startY, int endX, int endY);
	Path FindPathDijkstra(int startX, int startY, int endX, int endY);
	Path FindPathAStar(int startX, int startY, int endX, int endY);

	void DrawPath(const Path& path, const X::Math::Vector4& color);

	//tile functions
	std::pair<int, int> WorldToGrid(float worldX, float worldY) const {
		int gridX = static_cast<int>(worldX / 32);
		int gridY = static_cast<int>(worldY / 32);
		return { gridX, gridY };
	}

	X::Math::Vector2 GridToWorld(int gridX, int gridY) const {
		float worldX = (gridX * 32) + 16;
		float worldY = (gridY * 32) + 16;
		return X::Math::Vector2{ worldX, worldY };
	}

	void InitializeTileWeights() {
		tileWeights = std::vector<std::vector<int>>(getRows(), std::vector<int>(getColumns(), 0));
	}
	void IncreaseTileWeight(int x, int y) {
		if (x >= 0 && x < getColumns() && y >= 0 && y < getRows()) {
			tileWeights[y][x]++;
		}
	}
	int GetTileWeight(int x, int y) const {
		if (x >= 0 && x < getColumns() && y >= 0 && y < getRows()) {
			return tileWeights[y][x];
		}
		return -1;
	}

private:
	//tileWeigts 
	std::vector<std::vector<int>> tileWeights;

	AI::GridBasedGraph mGraph;
	std::vector<int> mMap;
	std::vector<Tile> mTiles;
	int mColumns = 0;
	int mRows = 0;
	int mTileWidth = 0;
	int mTileheight = 0;
};