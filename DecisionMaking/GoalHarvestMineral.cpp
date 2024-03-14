#include "GoalHarvestMineral.h"

GoalHarvestMineral::GoalHarvestMineral()
{
}
void GoalHarvestMineral::Activate(Raven& agent)
{
	mStartTime = X::GetTime();
}
GoalHarvestMineral::Status GoalHarvestMineral::Process(Raven& agent)
{
	if(mStartTime +0.5f < X::GetTime())
	{
		Mineral* mineral = (Mineral*)agent.target;
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

