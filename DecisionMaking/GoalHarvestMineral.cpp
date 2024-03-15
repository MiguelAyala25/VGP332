#include "GoalHarvestMineral.h"
#include "Mineral.h"
#include "TypeIds.h"

GoalHarvestMineral::GoalHarvestMineral()
{

}
void GoalHarvestMineral::Activate(Raven& agent)
{
	mStartTime = X::GetTime();
}
GoalHarvestMineral::Status GoalHarvestMineral::Process(Raven& agent)
{
	Mineral* mineral = nullptr;
	AI::EntityPtrs minerals = agent.world.GetEntitiesInRange({agent.destination, 1.0f}, static_cast<uint32_t>(AgentType::Mineral));
	if (!minerals.empty())
	{
		mineral = static_cast<Mineral*>(minerals[0]);
	}
	if (agent.target == nullptr || agent.target->GetTypeId() != static_cast<uint32_t>(AgentType::Mineral))
	{
		mStatus = GoalHarvestMineral::Status::Failed;
	}

	else if(mStartTime + 0.5f < X::GetTime())
	{
		agent.target = &agent;
		if (mineral != nullptr)
		{
			mineral->SetHealth(0);
		}
		return mStatus;

	}
}

void GoalHarvestMineral::Terminate(Raven& agent)
{
}

