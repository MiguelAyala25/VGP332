#include "Mineral.h"
#include "TypeIds.h"

Mineral::Mineral(AI::AIWorld& world)
	: Entity(world, static_cast<uint32_t>(AgentType::Mineral))
{
}

void Mineral::Initialize(const X::Math::Vector2& spawnPosition)
{
	mTextureId = X::LoadTexture("mushroom.png");
	position = spawnPosition;
}

void Mineral::Render()
{
	if (!IsCollected())
	{
		X::DrawSprite(mTextureId, position);
	}
}