#include "Pilot.h"
#include "PilotStates.h"
#include "ImGui/Inc/imgui.h"

void Pilot::Initialize()
{
	mLocation = PilotLocation::Barraks;
	mechHp = 100;
	enemyHp = 200;

	mStateMachine.Initialize(this);
	mStateMachine.AddState<RestingInBarraksState>();
	mStateMachine.AddState<PreparingMechForActionState>();
	mStateMachine.AddState<MovingToLocation>();
	mStateMachine.AddState<FightingEnemies>();
	ChangeStates(PilotState::RestingInBarraks);
}

void Pilot::Terminate()
{
	mStateMachine.Terminate();
}

void Pilot::Update(float deltaTime)
{
	mStateMachine.Update(deltaTime);
}

void Pilot::ChangeStates(PilotState newState)
{
	mStateMachine.ChangeState((int)newState);
}

void Pilot::DebugUI()
{
	mStateMachine.DebugUI();
	ImGui::Text("Status: MechHP[%d] EnemyHP[%d] ", mechHp, enemyHp);
}

PilotLocation Pilot::getLocation() const
{
	return PilotLocation();
}

bool Pilot::CanFight() const
{
	return mechHp>=30;
}

bool Pilot::OrderReceived() const
{
	//this returns a random bool
	static std::random_device rd;  
	static std::mt19937 rng(rd()); 
	std::uniform_int_distribution<int> uni(0, 1);
	return uni(rng);
}


bool Pilot::IspilotReady() const
{
	return mechHp==100;
}


bool Pilot::IsEnemyDestroyed() const
{
	return enemyHp<=0;
}

void Pilot::SetLocation(PilotLocation location)
{
	mLocation = location;
}

void Pilot::RepairMech()
{
	mechHp = 100;
}

void Pilot::fight()
{
	mechHp -= 10;
	enemyHp -= 10;
}

void Pilot::HealEnemy()
{
	if (enemyHp<=0)
	{
		enemyHp = 200;
	}
}

