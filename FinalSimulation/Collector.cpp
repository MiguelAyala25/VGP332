#include "Collector.h"
#include "TypeIds.h"

Collector::Collector(AI::AIWorld& world, TileMap& tileMap)
	: Entity(world, static_cast<uint32_t>(AgentType::Collector)), tileMap(tileMap)
{
}

void Collector::Initialize(const X::Math::Vector2& spawnPosition)
{
	mTextureId = X::LoadTexture("scv_09.png");
	position = spawnPosition;
    //save this to be able to return
    Spawnposition = spawnPosition;
}

void Collector::Render()
{
	X::DrawSprite(mTextureId, position);
    DrawPath();
}

void Collector::Update(float deltaTime)
{
    if (isMoving) {
        FollowPath(deltaTime);
    }
    CheckForMinerals();
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

    if (timeSinceLastMove >= .2f) {
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
  
void Collector::CheckForMinerals() {
    auto collectorTilePos = tileMap.WorldToGrid(position.x, position.y);

    for (auto it = minerals->begin(); it != minerals->end();) {
        auto mineralTilePos = tileMap.WorldToGrid((*it)->GetPosition().x, (*it)->GetPosition().y);
        if (collectorTilePos == mineralTilePos) {
            it = minerals->erase(it);
            //will replace spawposition to the pos of another mineral later
            MoveTo(Spawnposition);
            break;
        }
        else {
            ++it;
        }
    }
}

void Collector::DrawPath() {
    if (currentPath.size() < 2) return; // Si el camino tiene menos de dos puntos, no hay nada que dibujar.

    for (size_t i = 0; i < currentPath.size() - 1; ++i) {
        const auto& from = currentPath[i];
        const auto& to = currentPath[i + 1];
        X::DrawScreenLine(from, to, X::Colors::Yellow); // Cambia el color si lo deseas.
    }
}