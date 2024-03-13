#pragma once
#include "AI.h"

class VisualSensor;

class SCV : public AI::Agent
{
public:
	SCV(AI::AIWorld& world);
	~SCV() override = default;

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ShowDebug(bool debug);

	void SetSeek(bool active);
	void SetFlee(bool active);
	void SetArrive(bool active);
	void SetWander(bool active);
	void SetPursuit(bool active);
	void SetSeparation(bool active);
	void SetAlignment(bool active);
	void SetCohesion(bool active);
	void SetEvade(bool active);

	void SetSeekWeight(float weight);
	void SetFleeWeight(float weight);
	void SetArriveWeight(float weight);
	void SetWanderWeight(float weight);
	void SetPursuitWeight(float weight);
	void SetSeparationWeight(float weight);
	void SetAlignmentWeight(float weight);
	void SetCohesionWeight(float weight);

	void SetEvadeWeight(float weight);
private:

	VisualSensor* mVisualSensor = nullptr;
	VisualSensor* mVisualSensor2 = nullptr;

	std::unique_ptr<AI::PerceptionModule> mPerceptionModule;
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	AI::SeekBehavior* mSeekBehavior = nullptr;
	AI::FleeBehavior* mFleeBehavior = nullptr;
	AI::ArriveBehavior* mArriveBehavior = nullptr;
	AI::WanderBehavior* mWanderBehavior = nullptr;
	AI::PursuitBehavior* mPursuitBehavior = nullptr;
	AI::SeparationBehavior* mSeparationBehavior = nullptr;
	AI::AlignmentBehavior* mAlignmentBehavior = nullptr;
	AI::CohesionBehavior* mCohesionBehavior = nullptr;
	AI::EvadeBehavior* mEvadeBehavior = nullptr;

	std::array<X::TextureId, 16> mTextureIds;
};