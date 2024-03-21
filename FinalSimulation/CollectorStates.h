#pragma once

#include "State.h"

class Collector;

class IdleState : public AI::State<Collector> {
public:
    void Enter(Collector& agent) override;
    void Update(Collector& agent, float deltaTime)override;
    void Exit(Collector& agent) override;
    void DebugUI() override;
};

class RecollectingState : public AI::State<Collector> {
public:
    void Enter(Collector& agent) override;
    void Update(Collector& agent, float deltaTime)override;
    void Exit(Collector& agent) override;
    void DebugUI() override;
};

class ReturningHomeState : public AI::State<Collector> {
public:
    void Enter(Collector& agent) override;
    void Update(Collector& agent, float deltaTime)override;
    void Exit(Collector& agent) override;
    void DebugUI() override;
};
