#pragma once
#include "Entity.h"

namespace AI
{
	using EntityPtrs = std::vector<Entity*>;
	class AIWorld
	{
	public:
		void Initialize();
		void Update();

		void Register(Entity* entity);
	private:
		mutable uint32_t mNext = 0;
		EntityPtrs mEntities;

	}


}