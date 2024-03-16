#include "Collector.h"
#include "TypeIds.h"

Collector::Collector(AI::AIWorld& world, TileMap& tileMap)
	: Entity(world, static_cast<uint32_t>(AgentType::Collector)), tileMap(tileMap)
{
}

void Collector::Initialize(const X::Math::Vector2& spawnPosition)
{
	mTextureId = X::LoadTexture("mushroom.png");
	position = spawnPosition;
}

void Collector::Render()
{
	X::DrawSprite(mTextureId, position);
}

void Collector::Update(float deltaTime)
{
    if (isMoving) {
        FollowPath(deltaTime);
    }
}

void Collector::MoveTo(const X::Math::Vector2& targetPosition)
{
    auto [startX, startY] = tileMap.WorldToGrid(position.x, position.y);
    auto [endX, endY] = tileMap.WorldToGrid(targetPosition.x, targetPosition.y);

    currentPath = tileMap.FindPathAStar(startX, startY, endX, endY);
    if (!currentPath.empty()) {
        isMoving = true;
        currentPathIndex = 0;
    }
}

void Collector::FollowPath(float deltaTime)
{
    timeSinceLastMove += deltaTime;

    if (timeSinceLastMove >= 1.0f) {
        if (currentPathIndex < currentPath.size()) {
            const X::Math::Vector2& nextPoint = currentPath[currentPathIndex];
            position = nextPoint;
            ++currentPathIndex;

            if (currentPathIndex >= currentPath.size()) {
                isMoving = false;
            }
            timeSinceLastMove = 0.0f;
        }
    }
}
  