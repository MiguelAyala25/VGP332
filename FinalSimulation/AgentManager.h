#pragma once
#include <XEngine.h>
#include "Collector.h"
#include "Mineral.h" 

class AgentManager {
public:
    void AssignMineralToCollector();

    void SetCollectorAgents(const std::vector<std::unique_ptr<Collector>>& collectors);
    void SetMinerals(std::vector<std::unique_ptr<Mineral>>& mineralsRef){minerals = &mineralsRef;}
    std::vector<std::unique_ptr<Mineral>>& GetMinerals() { return *minerals; }



private:
    std::vector<Collector*> collectorAgents;
    std::vector<std::unique_ptr<Mineral>>* minerals;
};
