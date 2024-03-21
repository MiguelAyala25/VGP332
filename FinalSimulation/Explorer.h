#pragma once

#include "Collector.h"
#include "VisualSensor.h"
#include "PerceptionModule.h"

class VisualSensor;

//Explorer states
enum class ExplorerState {
    Idle,
    Exploring,
    Returning
};

class Explorer : public Collector {
public:
    Explorer(AI::AIWorld& world, TileMap& tileMap)
        : Collector(world, tileMap) {}

    //Collector methods 
    void Initialize(const X::Math::Vector2& spawnPosition) override;
    void Update(float deltaTime) override;

   void FollowPath(float deltaTime) override;

   void MoveTo(const X::Math::Vector2& targetPosition) override;

    //Explorer methods
    void Wander();
    void DiscoverResources();


    const Path& GetCurrentPath() const {
        return currentPath;
    }

private:
    X::Math::Vector2 velocity;
    //perception
    std::unique_ptr<AI::PerceptionModule> mPerceptionModule;
    VisualSensor* mVisualSensor = nullptr;

    //state machine 
    AI::StateMachine<Explorer> mStateMachine;
};
