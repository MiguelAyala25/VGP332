#pragma once

#include <XEngine.h>
#include <AI.h>

class Mineral : public AI::Entity
{
public:
	Mineral(AI::AIWorld& world);

	void Initialize(const X::Math::Vector2& spawnPosition);
	void Render();

private:
	X::TextureId mTextureId;
};