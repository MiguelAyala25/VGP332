#pragma once
#include <AI.h>
#include  "TypeIds.h"

class VisualSensor : public AI::Sensor {

public:

	virtual void Update(AI::Agent& agent, AI::MemoryRecords& memory, float deltaTime) = 0;

	AgentType agentType = AgentType::Invalid;

	float viewRange = 0.0f;
	float viewAnge = 0.0f;



	//Pienso en ti todo el tiempo
};
