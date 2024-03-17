#include "Explorer.h"

void Explorer::Initialize(const X::Math::Vector2& spawnPosition)
{
	mTextureId = X::LoadTexture("interceptor_01.png");
	position = spawnPosition;
	//save this to be able to return
	Spawnposition = spawnPosition;
}

void Explorer::Update(float deltaTime)
{
	if (isMoving) {
		FollowPath(deltaTime);
	}
}

void Explorer::FollowPath(float deltaTime)
{
    timeSinceLastMove += deltaTime;

    if (timeSinceLastMove >= .2f) {
        if (currentPathIndex < currentPath.size()) {
            const X::Math::Vector2& nextPoint = currentPath[currentPathIndex];
            position = nextPoint;
            ++currentPathIndex;

            if (currentPathIndex >= currentPath.size()) {
                isMoving = false;
                Wander();
            }
            timeSinceLastMove = 0.0f;
        }
    }
}

void Explorer::Wander()
{
    //initialize randoms eed
    static bool isSeedSet = false;
    if (!isSeedSet) {
        srand(static_cast<unsigned int>(time(nullptr)));
        isSeedSet = true;
    }

    //List of posible directions
    const std::vector<std::pair<int, int>> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1} 
    };

    auto [currentX, currentY] = tileMap.WorldToGrid(position.x, position.y);

    int lowestWeight = INT_MAX;
    std::vector<std::pair<int, int>> bestTiles;

    //Check every direction
    for (const auto& dir : directions) {
        int newX = currentX + dir.first;
        int newY = currentY + dir.second;

        //Is it a valid tile?
        if (tileMap.IsCommonTile(newX, newY)) {
            int tileWeight = tileMap.GetTileWeight(newX, newY);

            //If we get a tile with less weight restart best tile list
            if (tileWeight < lowestWeight) {
                bestTiles.clear();
                lowestWeight = tileWeight;
                bestTiles.push_back({ newX, newY });
            }
            else if (tileWeight == lowestWeight) {
                //same weight goes to option list
                bestTiles.push_back({ newX, newY });
            }
        }
    }

    //Rnadom chose in best tiles
    if (!bestTiles.empty()) {
        auto [chosenX, chosenY] = bestTiles[rand() % bestTiles.size()];

        MoveTo(tileMap.GridToWorld(chosenX, chosenY));
        tileMap.IncreaseTileWeight(chosenX, chosenY);
    }
}

