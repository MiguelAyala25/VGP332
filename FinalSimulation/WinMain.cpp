#include "TileMap.h"
#include <XEngine.h> // <> for external includes, "" for internal includes
#include <ImGui/Inc/imgui.h>
#include <AI.h>

//agents
#include "Collector.h"
#include "Explorer.h"

//resources 
#include "Mineral.h"

//manager
#include "AgentManager.h"

AgentManager agentManager;


using namespace AI;

AIWorld aiWorld;
X::Math::Vector2 destination = X::Math::Vector2::Zero();

//collectors 
std::vector<std::unique_ptr<Collector>> collectorAgents;
int numCollectors = 5;

//explorers
std::vector<std::unique_ptr<Explorer>> explorerAgents;
int numExplorers = 2;

//Resoucers
std::vector<std::unique_ptr<Mineral>> minerals;
int mineralNum = 30;

//tileMaps
TileMap tileMap;
X::TextureId textureId;
X::Math::Vector2 position;
Path path;

int endX = 12;
int endY = 11;

int endX1 = 7;
int endY1 = 12;


float mineralReductionTimer = 0.0f;
const float reductionInterval = 10.0f;


bool showDebug = false;
//--------------------------------------------------

X::Math::Vector2 GenerateRandomNonBaseTilePosition(TileMap& tileMap)
{
	std::vector<X::Math::Vector2> nonBaseTilePositions;

	for (int y = 0; y < tileMap.getRows(); ++y) {
		for (int x = 0; x < tileMap.getColumns(); ++x) {
			if (tileMap.IsCommonTile(x, y)) {
				nonBaseTilePositions.push_back(tileMap.GetPixelPosition(x, y));
			}
		}
	}
	int randomIndex = X::Random(0, static_cast<int>(nonBaseTilePositions.size()) - 1);
	return nonBaseTilePositions[randomIndex];
}

void InitializeAgents()
{

	std::vector<X::Math::Vector2> baseTilesPositions;
	//Gets the "Base tiles"
	for (int y = 0; y < tileMap.getRows(); ++y) {
		for (int x = 0; x < tileMap.getColumns(); ++x) {
			if (tileMap.IsBaseTile(x, y) == true) {
				baseTilesPositions.push_back(tileMap.GetPixelPosition(x, y));
			}
		}
	}

	//Spawns the agents on random tiles inside the base tiles
	for (int i = 0; i < numCollectors; ++i) {
		if (!baseTilesPositions.empty()) {
			int randomIndex = X::Random(0, static_cast<int>(baseTilesPositions.size()) - 1);
			//collectors
			auto& collector = collectorAgents.emplace_back(std::make_unique<Collector>(aiWorld, tileMap));
			collector->SetMineralsReference(minerals);
			collector->Initialize(baseTilesPositions[randomIndex]);

			baseTilesPositions.erase(baseTilesPositions.begin() + randomIndex);
		}
	}
	for (int i = 0; i < numExplorers; ++i) {
		if (!baseTilesPositions.empty()) {
			int randomIndex = X::Random(0, static_cast<int>(baseTilesPositions.size()) - 1);

			//explorers
			auto& explorer = explorerAgents.emplace_back(std::make_unique<Explorer>(aiWorld, tileMap, agentManager));
			explorer->Initialize(baseTilesPositions[randomIndex]);
			explorer->SetTargetPosition(GenerateRandomNonBaseTilePosition(tileMap));

			baseTilesPositions.erase(baseTilesPositions.begin() + randomIndex);
		}
	}

	agentManager.SetCollectorAgents(collectorAgents);
}

void InitalizeResources()
{

	for (int i = 0; i < mineralNum; ++i) {
		X::Math::Vector2 randomPosition = GenerateRandomNonBaseTilePosition(tileMap);
		auto& mineral = minerals.emplace_back(std::make_unique<Mineral>(aiWorld));
		mineral->Initialize(randomPosition);
	}

}

void GameInit()
{
	aiWorld.Initialize();
	tileMap.LoadTiles("tiles.txt");
	tileMap.LoadMap("map.txt");

	tileMap.InitializeTileWeights();

	InitalizeResources();
	InitializeAgents();
	agentManager.SetMinerals(minerals);


	/*if (!explorerAgents.empty() && !minerals.empty()) {
		explorerAgents.front()->SetTargetPosition(GenerateRandomNonBaseTilePosition(tileMap));
	}*/
}

bool GameLoop(float deltaTime)
{
	/*
	static float timer = 0.0f; 
	timer += deltaTime;

	if (timer >= 5.0f) {
		timer -= 5.0f;
		agentManager.RemoveCollectedMineral();
	}


	if (agentManager.GetNumCollectedMinerals() > 5)
	{
		for (auto& agent : explorerAgents)
		{
			agent->SetBackHomeStatus(true);
		}
	}
	else
	{
		for (auto& agent : explorerAgents)
		{
			agent->SetHasTarget(true);
		}
	}*/



	tileMap.Render(showDebug);
	//agent updates
	for (auto& agent : collectorAgents)
	{
		agent->Update(deltaTime);
		agent->Render();
	}

	for (auto& agent : explorerAgents)
	{
		agent->Update(deltaTime);
		agent->Render();
	}

	//resources update
	for (auto& mineral : minerals)
	{
		mineral->Render();
	}

	agentManager.AssignMineralToCollector();

	ImGui::Begin("Steering", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	{
		ImGui::Text("Minerals: %d", agentManager.GetNumCollectedMinerals());

		if (ImGui::Button("Add minerals"))
		{
			InitalizeResources();

		}
		if (ImGui::Button("show Debug?"))
		{
			showDebug = true;
		}
		if (ImGui::Button("BackHome"))
		{
			for (auto& agent : explorerAgents)
			{
				agent->SetBackHomeStatus(true);
			}
		}

	}

	ImGui::End();
	
	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);

	return quit;
}

void GameCleanup()
{

}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Pathfinding");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}