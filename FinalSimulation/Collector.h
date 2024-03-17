#pragma once

#include <XEngine.h>
#include <AI.h>
#include "TileMap.h" 
#include "Mineral.h"


class Collector : public AI::Entity
{
public:
	Collector(AI::AIWorld& world, TileMap& tileMap);

	virtual void Initialize(const X::Math::Vector2& spawnPosition);
	virtual void Update(float deltaTime);

	void Render();
	virtual void MoveTo(const X::Math::Vector2& targetPosition);
	void CheckForMinerals();

	void DrawPath();

	//minerals reference
	std::vector<std::unique_ptr<Mineral>>* minerals;
	void SetMineralsReference(std::vector<std::unique_ptr<Mineral>>& mineralsRef) {
		minerals = &mineralsRef;
	}

protected:
	X::TextureId mTextureId;
	TileMap& tileMap;

	X::Math::Vector2 Spawnposition;

	Path currentPath;
	size_t currentPathIndex = 0;

	bool isMoving = false;
	float timeSinceLastMove = 0.0f;

	virtual void FollowPath(float deltaTime);
};