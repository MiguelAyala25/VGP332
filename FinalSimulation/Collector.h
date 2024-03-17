#pragma once

#include <XEngine.h>
#include <AI.h>
#include "TileMap.h" 
#include "Mineral.h"

class VisualSensor;

class Collector : public AI::Entity
{
public:
	Collector(AI::AIWorld& world, TileMap& tileMap);

	void Initialize(const X::Math::Vector2& spawnPosition);
	void Render();

	void Update(float deltaTime); 
	void MoveTo(const X::Math::Vector2& targetPosition);
	void CheckForMinerals();

	//minerals reference
	std::vector<std::unique_ptr<Mineral>>* minerals;
	void SetMineralsReference(std::vector<std::unique_ptr<Mineral>>& mineralsRef) {
		minerals = &mineralsRef;
	}

private:
	X::TextureId mTextureId;
	TileMap& tileMap;

	X::Math::Vector2 Spawnposition;

	Path currentPath;
	size_t currentPathIndex = 0;

	bool isMoving = false;
	float timeSinceLastMove = 0.0f;

	void FollowPath(float deltaTime);
};