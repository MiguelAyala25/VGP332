#include "Precompiled.h"
#include "EvadeBehavior.h"
#include "Agent.h"

using namespace AI;

X::Math::Vector2 EvadeBehavior::Calculate(Agent& agent)
{
    // Check if the agent has a target. If not, return a zero vector.
    if (agent.target == nullptr)
    {
        return X::Math::Vector2();
    }

    // Calc vect from the target to agent
    X::Math::Vector2 targetToAgent = agent.position - agent.target->position;
    //Calc distance from the target to agent
    float distToTarget = X::Math::Magnitude(targetToAgent);
    //return zero if agent is close
    if (distToTarget <= 10.0f)
    {
        return X::Math::Vector2();
    }

    //Calctime it take for the agent to reach the target
    const float timeToTarget = distToTarget / agent.maxSpeed;
    const X::Math::Vector2& targetPosition = agent.target->position;
    const X::Math::Vector2& targetVelocity = agent.target->velocity;
    // Predict the future position of the agent with pos and vel
    const X::Math::Vector2 predictedPosition = agent.position - (targetVelocity * timeToTarget);

    //recal vect
    targetToAgent = predictedPosition - agent.position;
    distToTarget = X::Math::Magnitude(targetToAgent);
    //return zero if very close
    if (distToTarget <= 10.0f)
    {
        return X::Math::Vector2();
    }

    // Calculate in opsite direction
    const X::Math::Vector2 desiredVelocity = (targetToAgent / distToTarget) * agent.maxSpeed;
    const X::Math::Vector2 evadeForce = desiredVelocity - agent.velocity;

    //debug
    if (IsDebug())
    {
        X::DrawScreenCircle(targetPosition, 20.0f, X::Colors::Red);
        X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
        X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Blue); 
    }

    return evadeForce;
}