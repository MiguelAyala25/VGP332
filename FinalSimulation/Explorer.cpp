#include "Explorer.h"
#include "TypeIds.h"
#include "ExplorerStates.h"

namespace {
    float ComputerImportance(const AI::Agent& agent, const AI::MemoryRecord& record)
    {
        float score = 0.0f;
        AgentType entityType = static_cast<AgentType>(record.GetProperty<int>("type"));
        switch (entityType)
        {
        case AgentType::Invalid:
            score = 0.0f;
            break;
        case AgentType::Mineral:
        {
            X::Math::Vector2 lastSeenPos = record.GetProperty<X::Math::Vector2>("lastSeenPosition");
            float distance = X::Math::Distance(agent.position, lastSeenPos);
            float distanceScore = std::max(1000.0f - distance, 0.0f);
            score = distanceScore;
        }
        break;
        default:
            break;
        }
        return score;
    }
}


void Explorer::Initialize(const X::Math::Vector2& spawnPosition)
{
    mTextureId = X::LoadTexture("interceptor_01.png");
    position = spawnPosition;
    //save this to be able to return
    Spawnposition = spawnPosition;

    mPerceptionModule = std::make_unique<AI::PerceptionModule>(*this, ComputerImportance);
    mPerceptionModule->SetMemorySpan(2.0f);

    mVisualSensor = mPerceptionModule->AddSensor<VisualSensor>();
    mVisualSensor->targetType = AgentType::Mineral;

    mStateMachine.AddState<ExplorerExploringState>();
    mStateMachine.ChangeState(static_cast<int>(ExplorerState::Idle));

}

void Explorer::Update(float deltaTime)
{
	if (isMoving) {
		FollowPath(deltaTime);
	}

    mVisualSensor->viewRange = 50;
    mVisualSensor->viewHalfAngle = 360 * X::Math::kDegToRad;
    mPerceptionModule->Update(deltaTime);

    DiscoverResources();
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

void Explorer::DiscoverResources()
{
    const auto& memoryRecords = mPerceptionModule->GetMemoryRecords();
    for (auto& memory : memoryRecords)
    {
        X::Math::Vector2 pos = memory.GetProperty<X::Math::Vector2>("lastSeenPosition");
        X::DrawScreenLine(position, pos, X::Colors::White);

        std::string score = std::to_string(memory.importance);
        X::DrawScreenText(score.c_str(), pos.x, pos.y, 12.0f, X::Colors::White);
    }
}

void Explorer::MoveTo(const X::Math::Vector2& targetPosition)
{
    auto [startX, startY] = tileMap.WorldToGrid(position.x, position.y);
    auto [endX, endY] = tileMap.WorldToGrid(targetPosition.x, targetPosition.y);

    currentPath = tileMap.FindPathAStar(startX, startY, endX, endY);
    if (!currentPath.empty()) {
        isMoving = true;
        currentPathIndex = 0;
    }
}