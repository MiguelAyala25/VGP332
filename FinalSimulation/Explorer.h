#pragma once

#include "Collector.h"
#include "VisualSensor.h"
#include "PerceptionModule.h"
#include "AgentManager.h"

class VisualSensor;

//Explorer states
enum class ExplorerState {
    Idle,
    MovingToPosition,
    Exploring,
    Returning
};

class Explorer : public Collector {
public:
    Explorer(AI::AIWorld& world, TileMap& tileMap, AgentManager& agentManager)
        : Collector(world, tileMap), agentManager(agentManager) {}

    //Collector methods 
    void Initialize(const X::Math::Vector2& spawnPosition) override;
    void Update(float deltaTime) override;

   void FollowPath(float deltaTime) override;

   void MoveTo(const X::Math::Vector2& targetPosition) override;

    //Explorer methods
    void Wander();
    void DiscoverResources();

    //get
    const Path& GetCurrentPath() const { return currentPath;}
    AI::StateMachine<Explorer>& GetExplorerStateMachine() { return mStateMachine;}
    bool GetBackHomeStatus() { return backHomeStatus; }
    void SetBackHomeStatus(bool SetBackHomeStatus) { backHomeStatus = SetBackHomeStatus; }

    //test
    X::Math::Vector2 GetNextWanderDestination() const { return nextWanderDestination; }

    bool HasReachedDestination();

private:
    bool backHomeStatus = false;
    //perception
    std::unique_ptr<AI::PerceptionModule> mPerceptionModule;
    VisualSensor* mVisualSensor = nullptr;

    //state machine 
    AI::StateMachine<Explorer> mStateMachine;
    X::Math::Vector2 nextWanderDestination;

    //agent manager 
    AgentManager& agentManager;

};
