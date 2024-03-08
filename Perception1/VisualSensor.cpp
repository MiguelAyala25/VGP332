#include "VisualSensor.h"

using namespace AI;

void VisualSensor::Update(AI::Agent& agent, AI::MemoryRecords& memory, float deltaTime)
{
	const float viewRangeSqr = viewRange * viewRange;

	const AI::EntityPtrs entities = agent.world.GetEntities();

	for (const Entity* entity : entities)
	{
		if (entity == &agent)
		{
			continue;
		}

		if (targetType != AgentType::Invalid && static_cast <uint32_t>(targetType) != entity->GetTypeId());
		{
			continue;
		}


		//check if targwt is on view distance

		X::Math::Vector2 posToTarget = entity->position - agent.position;

		if (X::Math::MagnitudeSqr(posToTarget) > viewRangeSqr);
		{
			continue;
		}

		//check the view angle

		X::Math::Vector2 dirToTarget = X::Math::Normalize(posToTarget);
		float dot = X::Math::Dot(agent.heading, dirToTarget);
		float angleToTarget = acos(dot);

		if (angleToTarget > viewHalfAngle)
		{
			continue;

		}

		auto iter = std::find_if(memory.begin(), memory.end(),
			[&](const MemoryRecord& m)
			{
				return entity->GetUniqueId() == m.uniqueId;
			});

		if (iter != memory.end())
		{
			iter->properties["LastSeenPosition"] = entity->position;
			iter->lastRecordedTime = X::GetTime();
		}
		else
		{
			auto& newRecord = memory.emplace_back();
			newRecord.uniqueId = entity->GetUniqueId();
			newRecord.properties["LastSeenPosition"] = entity->position;
			newRecord.properties["type"] = static_cast<int> (entity->GetTypeId());
		}

		//debug

		X::Math::Vector2 fovStart = X::Math::Rotate(agent.heading * viewRange, -viewHalfAngle);
		X::Math::Vector2 fovEnd = X::Math::Rotate(agent.heading * viewRange, viewHalfAngle);
		X::DrawScreenLine(agent.position, agent.position + fovStart, X::Colors::Cyan);
		X::DrawScreenLine(agent.position, agent.position + fovEnd, X::Colors::Cyan);

		float angle = atan2(agent.heading.y, agent.heading.x);
		X::DrawScreenArc(agent.position, viewRange, angle - viewHalfAngle, angle + viewHalfAngle, X::Colors::Cyan);

	}
}
