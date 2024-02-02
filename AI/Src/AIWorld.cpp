#include "AIWorld.h"
#include "Precompiled.h"

void AI::AIWorld::Initialize()
{
}

void AI::AIWorld::Update()
{
}

void AI::AIWorld::Register(Entity* entity)
{
	XASSERT(std::find(mEntities.begin(), mEntities.end(), entity) == mEntities.end(),
		"AIWorld: entity is already added");

	mEntities.push_back(entity);
}

void AI::AIWorld::Unregister(Entity* entity)
{
	auto iter = std::find(mEntities.begin(), mEntities.end(), entity);

	if (iter != mEntities.end())
	{
		mEntities.erase(iter);
	}

}
