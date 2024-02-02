#pragma once
#include "AI.h"

namespace AI
{
	class AIWorld;

	class Entity
	{
	public:
		Entity(AIWorld& world, int typedId);
		virtual ~Entity();
		Entity(const Entity&) = delete;
		Entity(const Entity&&) = delete;
		Entity& operator = (const Entity&)=delete;
		Entity& operator = (const Entity&&) = delete;

		AIWorld& world;
		X::Math::Vector2 position = X::Math::Vector2::Zero();
		X::Math::Vector2 heading = X::Math::Vector2::YAxis();
		float radius = 1.0f;

		X::Math::Matrix3 GetWorldTransform();
		int32_t getTypeId() const {
			return static_cast<int32_t
			>
				(mUniqueId >> 32);
		}
		int32_t getTypeId() const {return (mUniqueId >> 32);}

	private:
		const uint64_t mUniqueId = 0;
	};
 }