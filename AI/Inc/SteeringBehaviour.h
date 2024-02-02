#pragma once

#include <XEngine.h>

namespace AI
{
	class  Agent;
	
	class SteeringBehavior
	{
	public:

		virtual ~SteeringBehavior() = default;
		virtual X::Math::Vector2 Calculate(Agent& agent) = 0;

		void SetWeight(float weight) { mWeight = weight; }
		float getWeight() { return mWeight; }

	private:

		float mWeight = 1;
		bool mActive = false;
		bool mDebug = false;
	};
}