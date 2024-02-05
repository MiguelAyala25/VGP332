#include "PilotStates.h"
#include <ImGui/Inc/imgui.h>
#include "Pilot.h"

void RestingInBarraksState::Enter(Pilot& agent)
{
	agent.SetLocation(PilotLocation::Barraks);
}

void RestingInBarraksState::Update(Pilot& agent, float deltaTime)
{
	if (agent.OrderReceived())
	{
		agent.ChangeStates(PilotState::PreparingMechForAction);
	}
	else
	{

	}
}

void RestingInBarraksState::Exit(Pilot& agent)
{
}

void RestingInBarraksState::DebugUI()
{
	ImGui::Text("RestingInBarraksState: Pilot is resting in barraks");
}

void PreparingMechForActionState::Enter(Pilot& agent)
{
	agent.SetLocation(PilotLocation::MechBay);
}

void PreparingMechForActionState::Update(Pilot& agent, float deltaTime)
{
	if (agent.CanFight()&&agent.OrderReceived())
	{
		agent.ChangeStates(PilotState::MovingToLocation);
	}
	else if(!agent.CanFight())
	{
		agent.RepairMech();
	}
	else
	{
		agent.ChangeStates(PilotState::RestingInBarraks);
	}
}

void PreparingMechForActionState::Exit(Pilot& agent)
{
}

void PreparingMechForActionState::DebugUI()
{
	ImGui::Text("PreparingMechForActionState:: Pilot is preparing mech for action");
}

void MovingToLocation::Enter(Pilot& agent)
{
	agent.SetLocation(PilotLocation::Exterior);
}

void MovingToLocation::Update(Pilot& agent, float deltaTime)
{
	agent.HealEnemy();

	if (!agent.CanFight())
	{
		agent.ChangeStates(PilotState::PreparingMechForAction);
	}
	else
	{
		agent.ChangeStates(PilotState::FightingEnemies);
	}

}

void MovingToLocation::Exit(Pilot& agent)
{
}

void MovingToLocation::DebugUI()
{
	ImGui::Text("MovingToLocation:: Pilot is piloting the mech to a location");
}

void FightingEnemies::Enter(Pilot& agent)
{
	agent.SetLocation(PilotLocation::combatZone);
}

void FightingEnemies::Update(Pilot& agent, float deltaTime)
{
	if (!agent.CanFight()|| agent.IsEnemyDestroyed())
	{
		agent.ChangeStates(PilotState::MovingToLocation);
	}
	else
	{
		agent.fight();
	}
}

void FightingEnemies::Exit(Pilot& agent)
{
}

void FightingEnemies::DebugUI()
{
	ImGui::Text("FightingEnemies:: Pilot is fighting enemies");
}
