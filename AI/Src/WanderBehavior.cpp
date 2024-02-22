#include "Precompiled.h"
#include "WanderBehavior.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 WanderBehavior::Calculate(Agent& agent)
{
	X::Math::Vector2 newWanderTarget = mLocalWanderTarget + (X::RandomUnitCircle() * mWanderJitter);

	newWanderTarget = X::Math::Normalize(newWanderTarget) * mWanderRadius;
	mLocalWanderTarget = newWanderTarget;

	newWanderTarget += X::Math::Vector2(0.0f, mWanderDistance);

	const X::Math::Matrix3 worldTransform = agent.GetWorldTransform();
	const X::Math::Vector2 worldWanderTarget = X::Math::TransformCoord(newWanderTarget, worldTransform);

	const X::Math::Vector2 agentToDest = worldWanderTarget - agent.position;
	const float distance = X::Math::Magnitude(agentToDest);
	if (distance <= 1.0f)
	{
		return X::Math::Vector2::Zero();
	}

	const X::Math::Vector2 desiredVelocity = (agentToDest / distance) * agent.maxSpeed;
	const X::Math::Vector2 seekForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		const X::Math::Vector2 wanderCenter = X::Math::TransformCoord({ 0.0f, mWanderDistance }, worldTransform);
		X::DrawScreenCircle(wanderCenter, mWanderRadius, X::Colors::Yellow);
		X::DrawScreenDiamond(worldWanderTarget, 3.0f, X::Colors::Orange);
		X::DrawScreenLine(agent.position, worldWanderTarget, X::Colors::Green);
	}

	return seekForce;
}

void WanderBehavior::Setup(float radius, float distance, float jitter)
{
	mWanderRadius = radius;
	mWanderDistance = distance;
	mWanderJitter = jitter;
}