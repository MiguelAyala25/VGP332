#include "AgentManager.h"

void AgentManager::AssignMineralToCollector() {
    for (auto& mineral : *minerals) {
        if (mineral->IsDiscovered()&&!mineral->IsCollected()&&!mineral->IsAssigned()) {
            for (auto& collector : collectorAgents) {
                if (!collector->HasTarget()) {
                    collector->SetTargetPosition(mineral->GetPosition());
                    mineral->SetAssigned(true);
                    break;
                }
            }
        }
    }
}

void AgentManager::SetCollectorAgents(const std::vector<std::unique_ptr<Collector>>& collectors) {
    collectorAgents.clear();
    for (const auto& collector : collectors) {
        collectorAgents.push_back(collector.get());
    }
}

int AgentManager::GetNumCollectedMinerals()
{
    int collectedMinerals = 0;

    for (auto& mineral : *minerals) {
        if (mineral->IsCollected())
        {
            ++collectedMinerals;
        }
    }
    return collectedMinerals;
}

void AgentManager::RemoveCollectedMineral() {
    for (auto it = minerals->begin(); it != minerals->end(); ++it) {
        if ((*it)->IsCollected()) {

            it = minerals->erase(it);
            return; 
        }
    }
}