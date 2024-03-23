#include "CollisionSensor.h"
#include "Agent.h"

using namespace AI;

void CollisionSensor::Update(Agent& agent, MemoryRecords& memory, float deltaTime)
{
    hasCollided = false;

    const EntityPtrs& entities = agent.world.GetEntities();
    for (const Entity* entity : entities)
    {
        // Ignore the agent itself
        if (entity == &agent)
        {
            continue;
        }

        // Filter by type if needed
        if (targetType != AgentType::Invalid && static_cast<uint32_t>(targetType) != entity->GetTypeId())
        {
            continue;
        }

        //(x2-x1)^2 + (y2-y1)^2 <= (r1+r2)^2
        //https://stackoverflow.com/questions/1736734/circle-circle-collision
        //All Entitiy has radius so we can use that

        float dx = entity->position.x - agent.position.x;
        float dy = entity->position.y - agent.position.y; 
        float distanceSquared = (dx * dx) + (dy * dy);

        float collisionDistanceSquared = (collisionRadius + entity->radius) * (collisionRadius + entity->radius); 

        //check for collision
        if (distanceSquared <= collisionDistanceSquared)
        {
            hasCollided = true; 

            //check if we already know this entity
            auto iter = std::find_if(memory.begin(), memory.end(),
                [&](const MemoryRecord& m) {
                    return entity->GetUniqueId() == m.uniqueId;
                });

            if (iter == memory.end())
            {
                MemoryRecord newRecord;
                newRecord.uniqueId = entity->GetUniqueId();
                newRecord.properties["lastSeenPosition"] = entity->position;
                newRecord.properties["type"] = static_cast<int>(entity->GetTypeId());
                newRecord.lastRecordedTime = X::GetTime();
                memory.push_back(newRecord);
            }
        }
    }
}