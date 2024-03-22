#pragma once

#include <XEngine.h>
#include <AI.h>
#include "TileMap.h" 
#include "Mineral.h"
#include "CollectorStates.h"


//Collector states
enum class CollectorState {
    Idle,
    Recollecting,
    Returning
};

class Collector : public AI::Agent {
public:
    Collector(AI::AIWorld& world, TileMap& tileMap);

    // Lifecycle Methods
    virtual void Initialize(const X::Math::Vector2& spawnPosition);
    virtual void Update(float deltaTime);
    void Render();

    // Movement and Path Management
    virtual void MoveTo(const X::Math::Vector2& targetPosition);
    virtual void FollowPath(float deltaTime);
    void DrawPath();
    bool IsMoving() const { return isMoving; }

    // Mineral Management
    void SetMineralsReference(std::vector<std::unique_ptr<Mineral>>& mineralsRef) {
        minerals = &mineralsRef;
    }
    void SetTargetPosition(const X::Math::Vector2& position) {
        targetPosition = position;
        hasTarget = true;
    }
    std::vector<std::unique_ptr<Mineral>>& GetMinerals() {return *minerals;}
    bool RemoveMineralAtPosition(const X::Math::Vector2& position);
    // State Management
    virtual AI::StateMachine<Collector>& GetStateMachine() { return mStateMachine; }
    virtual void ExitIdleState() { mStateMachine.ChangeState(static_cast<int>(CollectorState::Recollecting)); }

    // Accessors
    X::Math::Vector2 GetSpawnposition() { return Spawnposition; }
    void SetHasTarget(bool targetAcitve) { hasTarget = targetAcitve; }
    bool HasTarget() const { return hasTarget; }
    const X::Math::Vector2& GetTargetPosition() const { return targetPosition; }
    void setIsMoving(bool IsMoving) { isMoving = IsMoving; }



protected:
    // Rendering
    X::TextureId mTextureId;

    // Environment
    TileMap& tileMap;
    X::Math::Vector2 Spawnposition;

    // Path and Movement
    Path currentPath;
    size_t currentPathIndex = 0;
    bool isMoving = false;
    float timeSinceLastMove = 0.0f;

    // Target and Mineral Management
    std::vector<std::unique_ptr<Mineral>>* minerals;
    X::Math::Vector2 targetPosition = X::Math::Vector2::Zero();
    bool hasTarget = false;

    // State Machine
    AI::StateMachine<Collector> mStateMachine;

};