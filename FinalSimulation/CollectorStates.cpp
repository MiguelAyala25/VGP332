#include "CollectorStates.h"
#include "Collector.h"

//idle state
void IdleState::Enter(Collector& agent) {
    // Implementación específica para cuando el agente entra en este estado
}

void IdleState::Update(Collector& agent, float deltaTime) {
    if (agent.HasTarget()) {
       agent.GetStateMachine().ChangeState(static_cast<int>(CollectorState::Recollecting));
    }
}

void IdleState::Exit(Collector& agent) {
    
}

void IdleState::DebugUI() {
 
}


//Recollecting state

void RecollectingState::Enter(Collector& agent) {
    agent.MoveTo(agent.GetTargetPosition());
}

void RecollectingState::Update(Collector& agent, float deltaTime) {
    if (agent.IsMoving()) {
        agent.FollowPath(deltaTime);
    }
    else {
        const auto& targetPos = agent.GetTargetPosition();
        if (agent.RemoveMineralAtPosition(targetPos)) {
            agent.SetHasTarget(false); //If there is no objetive
            agent.GetStateMachine().ChangeState(static_cast<int>(CollectorState::Returning)); //change to returning
        }
    }
}

void RecollectingState::Exit(Collector& agent) {
 
}

void RecollectingState::DebugUI() {
   
}

//going back state
void ReturningHomeState::Enter(Collector& agent) {
    agent.MoveTo(agent.GetSpawnposition());
}

void ReturningHomeState::Update(Collector& agent, float deltaTime) {
    if (agent.IsMoving()) {
        agent.FollowPath(deltaTime);
    }
    else {
        agent.GetStateMachine().ChangeState(static_cast<int>(CollectorState::Idle));
    }
}

void ReturningHomeState::Exit(Collector& agent) {

}

void ReturningHomeState::DebugUI() {

}