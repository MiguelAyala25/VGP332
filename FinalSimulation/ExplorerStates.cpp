#include "ExplorerStates.h"
#include "Explorer.h"

#include <cmath> // Include for std::abs
#include "XEngine.h" 

void ExplorerIdleState::Enter(Explorer& agent)
{

}

void ExplorerIdleState::Update(Explorer& agent, float deltaTime)
{
   if (agent.HasTarget()) {
       agent.GetExplorerStateMachine().ChangeState(static_cast<int>(ExplorerState::MovingToPosition));
    }
}

void ExplorerIdleState::Exit(Explorer& agent)
{
}

void ExplorerIdleState::DebugUI()
{
}

//Moving To position State

void ExplorerMovingToPositionState::Enter(Explorer& agent)
{
    agent.MoveTo(agent.GetTargetPosition());
}

void ExplorerMovingToPositionState::Update(Explorer& agent, float deltaTime)
{
    if (agent.IsMoving()) {
        agent.FollowPath(deltaTime);
    }
    else {
        const auto& targetPos = agent.GetTargetPosition();
        const float tolerance = 0.001f;
        if (std::abs(agent.position.x - targetPos.x) < tolerance &&
            std::abs(agent.position.y - targetPos.y) < tolerance)
        {
            agent.SetHasTarget(false);
            agent.GetStateMachine().ChangeState(static_cast<int>(ExplorerState::Exploring));
        }
    }
}

void ExplorerMovingToPositionState::Exit(Explorer& agent)
{
}

void ExplorerMovingToPositionState::DebugUI()
{
}

//exploring State

void ExplorerExploringState::Enter(Explorer& agent)
{
}

void ExplorerExploringState::Update(Explorer& agent, float deltaTime)
{
}

void ExplorerExploringState::Exit(Explorer& agent)
{
}

void ExplorerExploringState::DebugUI()
{
}

//returning home state 

void ExplorerReturningHomeState::Enter(Explorer& agent)
{
}

void ExplorerReturningHomeState::Update(Explorer& agent, float deltaTime)
{
}

void ExplorerReturningHomeState::Exit(Explorer& agent)
{
}

void ExplorerReturningHomeState::DebugUI()
{
}
