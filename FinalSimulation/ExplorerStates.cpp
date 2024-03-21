#include "ExplorerStates.h"
#include "Explorer.h"

#include <cmath>
#include "XEngine.h" 

#include <ImGui/Inc/imgui.h>

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
    agent.setIsMoving(true);
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
            agent.GetExplorerStateMachine().ChangeState(static_cast<int>(ExplorerState::Exploring));
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
    if (agent.GetBackHomeStatus()) {
        agent.GetExplorerStateMachine().ChangeState(static_cast<int>(ExplorerState::Returning));
    }
    else {
        // Aquí se decide si se necesita elegir un nuevo destino.
        if (!agent.IsMoving() || agent.HasReachedDestination()) { // Asumiendo que tienes una forma de verificar si ha llegado al destino.
            agent.Wander(); // Esto establecería el nuevo destino.
            agent.MoveTo(agent.GetNextWanderDestination()); // Esto inicia el movimiento hacia el destino.
        }
    }
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
    agent.MoveTo(agent.GetSpawnposition());

}

void ExplorerReturningHomeState::Update(Explorer& agent, float deltaTime)
{
    if (agent.IsMoving()) {
        agent.FollowPath(deltaTime);
    }
    else {
        agent.GetExplorerStateMachine().ChangeState(static_cast<int>(ExplorerState::Idle));
    }
}

void ExplorerReturningHomeState::Exit(Explorer& agent)
{
}

void ExplorerReturningHomeState::DebugUI()
{
}
