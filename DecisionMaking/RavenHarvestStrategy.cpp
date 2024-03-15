#include "RavenHarvestStrategy.h"
#include "TypeIds.h"
#include "GoalHarvestMineral.h"


float RavenHarvestStrategy::CalculateDesirability(Raven& agent) const
{
	AI::EntityPtrs minerals = agent.world.GetEntitiesInRange({ agent.destination, 1.0f }, static_cast<uint32_t>(AgentType::Mineral));

	if (!minerals.empty())
	{
		agent.target = static_cast<AI::Agent*>(minerals[0]);
	}
	if (agent.target != nullptr && agent.target->GetTypeId() == static_cast<uint32_t>(AgentType::Mineral))
	{
		if (X::Math::DistanceSqr(agent.position, agent.destination) < 25.0f)
		{
			return 1000;
		}
	}
	return 0.0f;
}

std::unique_ptr<AI::Goal<Raven>> RavenHarvestStrategy::CreateGoal() const
{
	auto newGoal = std::make_unique<GoalHarvestMineral>();
	return newGoal;
}