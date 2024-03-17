#pragma once

#include "Collector.h"

class VisualSensor;

class Explorer : public Collector {
public:
    Explorer(AI::AIWorld& world, TileMap& tileMap)
        : Collector(world, tileMap) {}

    //Collector methods 
    void Initialize(const X::Math::Vector2& spawnPosition) override;
    void Update(float deltaTime) override;

   void FollowPath(float deltaTime) override;

    //Explorer methods
    void Wander();
    void DiscoverResources();

private:
    X::Math::Vector2 velocity;
};
