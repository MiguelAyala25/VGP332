#pragma once

#include <cmath>
#include "XEngine.h" 

#include "State.h"

class Explorer;

class ExplorerIdleState : public AI::State<Explorer> {
public:
    void Enter(Explorer& agent) override;
    void Update(Explorer& agent, float deltaTime) override;
    void Exit(Explorer& agent) override;
    void DebugUI() override;
};

class ExplorerMovingToPositionState : public AI::State<Explorer> {
public:
    void Enter(Explorer& agent) override;
    void Update(Explorer& agent, float deltaTime) override;
    void Exit(Explorer& agent) override;
    void DebugUI() override;
};

class ExplorerExploringState : public AI::State<Explorer> {
public:
    void Enter(Explorer& agent) override;
    void Update(Explorer& agent, float deltaTime) override;
    void Exit(Explorer& agent) override;
    void DebugUI() override;
};

class ExplorerReturningHomeState : public AI::State<Explorer> {
public:
    void Enter(Explorer& agent) override;
    void Update(Explorer& agent, float deltaTime) override;
    void Exit(Explorer& agent) override;
    void DebugUI() override;
};
