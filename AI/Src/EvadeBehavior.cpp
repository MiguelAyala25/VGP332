#include "Precompiled.h"
#include "EvadeBehavior.h"
#include "Agent.h"

using namespace AI;

X::Math::Vector2 EvadeBehavior::Calculate(Agent& agent)
{
    const X::Math::Vector2 destToAgent = agent.position - agent.destination;

    if (X::Math::MagnitudeSqr(destToAgent) <= 1.0f)
    {
        return X::Math::Vector2::Zero();
    }
   
    // If we got the desired speed  we run, we norm and mult to max speed
    const X::Math::Vector2 desiredVelocity = X::Math::Normalize(destToAgent) * agent.maxSpeed;
    const X::Math::Vector2 evadeForce = desiredVelocity - agent.velocity;

    if (IsDebug())
    {
        X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
        X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
        X::DrawScreenCircle(agent.destination, 20.0f, X::Colors::Red);
    }

    return evadeForce;
}