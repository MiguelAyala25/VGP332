#pragma once

#include <XEngine.h>
#include <AI.h>

class Mineral : public AI::Entity
{
public:
	Mineral(AI::AIWorld& world);

	void Initialize(const X::Math::Vector2& spawnPosition);
	void Render();

	X::Math::Vector2 GetPosition() const { return position; }

	void SetDiscovered(bool discovered) { isDiscovered = discovered; }
	bool IsDiscovered() const { return isDiscovered; }

	void Collect() {isCollected = true;}
	bool IsCollected() const {return isCollected;}

	void SetAssigned(bool assigned) { this->assigned = assigned; }
	bool IsAssigned() const { return assigned; }


private:
	X::TextureId mTextureId;
	bool isDiscovered = false;
	bool isCollected = false;
	bool assigned = false;
};