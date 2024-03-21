#include "ExplorerStates.h"
#include "Explorer.h"

//idle state

void ExplorerIdleState::Enter(Explorer& agent)
{

}

void ExplorerIdleState::Update(Explorer& agent, float deltaTime)
{
    if (agent.HasTarget()) {
        agent.GetStateMachine().ChangeState(static_cast<int>(ExplorerState::Exploring));
    }
}

void ExplorerIdleState::Exit(Explorer& agent)
{
}

void ExplorerIdleState::DebugUI()
{
}

//Exploring state

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
