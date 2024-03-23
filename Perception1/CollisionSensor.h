#pragma once

#include <AI.h>
#include "TypeIds.h"

class CollisionSensor : public AI::Sensor
{
public:
    virtual void Update(AI::Agent& agent, AI::MemoryRecords& memory, float deltaTime) override;
    AgentType targetType = AgentType::Invalid;

    void SetCollisionRadius(float radius) { collisionRadius = radius; };
    float GetCollisionRadious() { return collisionRadius; }

    bool HasCollided() { return hasCollided; }

private:
    float collisionRadius = 50.0f;
    bool hasCollided = false;
};
