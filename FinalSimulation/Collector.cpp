#include "Collector.h"
#include "TypeIds.h"

Collector::Collector(AI::AIWorld& world, TileMap& tileMap)
	: Agent(world, static_cast<uint32_t>(AgentType::Collector)), tileMap(tileMap)
{
}

void Collector::Initialize(const X::Math::Vector2& spawnPosition)
{
    mTextureId = X::LoadTexture("scv_09.png");
    position = spawnPosition;
    Spawnposition = spawnPosition;

    mStateMachine.AddState<IdleState>();
    mStateMachine.AddState<RecollectingState>();
    mStateMachine.AddState<ReturningHomeState>();

    mStateMachine.Initialize(this);
    mStateMachine.ChangeState(static_cast<int>(CollectorState::Idle));
}

void Collector::Render()
{
	X::DrawSprite(mTextureId, position);
    DrawPath();
}

void Collector::Update(float deltaTime)
{
    mStateMachine.Update(deltaTime);
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

void Collector::DrawPath() {
    if (currentPath.size() < 2) return; //if path less than 2 points dont draw

    for (size_t i = 0; i < currentPath.size() - 1; ++i) {
        const auto& from = currentPath[i];
        const auto& to = currentPath[i + 1];
        X::DrawScreenLine(from, to, X::Colors::Yellow);
    }
}

bool Collector::RemoveMineralAtPosition(const X::Math::Vector2& position) {
    for (auto it = minerals->begin(); it != minerals->end(); ++it) {
        const auto& mineralPos = (*it)->GetPosition();

        if (mineralPos.x == position.x && mineralPos.y == position.y && (*it)->IsDiscovered()) {
            (*it)->Collect();
            return true;
        }
    }
    return false;
}