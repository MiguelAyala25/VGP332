#include "SCV.h"
#include "TypeIDS.h"

SCV::SCV(AI::AIWorld& world): Agent(world,static_cast<uint32_t>(AgentType::SCV))
{
}

void SCV::Load()
{
	for (int = 0; i < mTextureIds.size(); ++i)
	{
		char name[128];
		sprintf_s(name, "scv_%02i.png", i + 1);
		mTextureIds[i] = X::LoadTexture(name);
	}

}

void SCV::unLoad()
{
}

void SCV::Update(float deltaTime)
{
}

void SCV::Render()
{
}

void SCV::ShowDebug(bool debug)
{
	const float angle = atan2(-heading.x, heading.y) + X::Math::kPi;
	const float percent = angle / X::Math::kTwoPi;
	const int frame = static_cast<int> (percent)

}
