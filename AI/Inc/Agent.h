#pragma once

#include "Entity.h"

namespace AI
{
	class Agent : public Entity
	{
	public:
		Agent(AIWorld& world, uint32_t typeId)
			: Entity(world, typeId)
		{
		}
		~Agent() override = default;
		std::vector<const Agent*> neighbors;
		const Agent* target = nullptr;
		X::Math::Vector2 destination = X::Math::Vector2::Zero();
		X::Math::Vector2 velocity = X::Math::Vector2::Zero();
		float maxSpeed = 100.0f;
		float mass = 1.0f;
	};
}