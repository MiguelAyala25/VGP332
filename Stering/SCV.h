#pragma once
#include "AI.h"

class SCV : public AI::Agent
{
public:
	SCV(AI::AIWorld& world);
	~SCV() override = default;

	void Load();
	void unLoad();

	void Update(float deltaTime);
	void Render();

	void ShowDebug(bool debug);

private:
	std::array<X::TextureId, 16> mTextureIds;

};