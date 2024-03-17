#include "TileMap.h"
#include <XEngine.h> // <> for external includes, "" for internal includes
#include <ImGui/Inc/imgui.h>
#include <AI.h>

//agents
#include "Collector.h"

//resources 
#include "Mineral.h"

using namespace AI;

AIWorld aiWorld;
X::Math::Vector2 destination = X::Math::Vector2::Zero();

//collectors 
std::vector<std::unique_ptr<Collector>> collectorAgents;
int numCollectors = 1;

//Resoucers
std::vector<std::unique_ptr<Mineral>> minerals;
int mineralNum = 10;

//tileMaps
TileMap tileMap;
X::TextureId textureId;
X::Math::Vector2 position;
Path path;




int endX = 15;
int endY = 11;


//--------------------------------------------------
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
			auto& collector = collectorAgents.emplace_back(std::make_unique<Collector>(aiWorld, tileMap));
			collector->Initialize(baseTilesPositions[randomIndex]);

			baseTilesPositions.erase(baseTilesPositions.begin() + randomIndex);
		}
	}
}

void InitalizeResources()
{
	auto& mineral = minerals.emplace_back(std::make_unique<Mineral>(aiWorld));
	// Coloca el mineral cerca del objetivo final para simplificar
	mineral->Initialize(tileMap.GetPixelPosition(endX, endY));

	/*std::vector<X::Math::Vector2> regularTilesPositions;

	//Gets the "non-base tiles"
	for (int y = 0; y < tileMap.getRows(); ++y) {
		for (int x = 0; x < tileMap.getColumns(); ++x) {
			if (tileMap.CanSpawnResources(x, y) == true) {
				regularTilesPositions.push_back(tileMap.GetPixelPosition(x, y));
			}
		}
	}
	//Spawns the agents on random tiles inside the base tiles
	for (int i = 0; i < mineralNum; ++i) {
		if (!regularTilesPositions.empty()) {
			int randomIndex = X::Random(0, static_cast<int>(regularTilesPositions.size()) - 1);
			auto& collector = minerals.emplace_back(std::make_unique<Mineral>(aiWorld));
			collector->Initialize(regularTilesPositions[randomIndex]);

			regularTilesPositions.erase(regularTilesPositions.begin() + randomIndex);
		}
	}*/

}

void GameInit()
{
	aiWorld.Initialize();
	tileMap.LoadTiles("tiles.txt");
	tileMap.LoadMap("map.txt");

	InitializeAgents();
	InitalizeResources();

	if (!collectorAgents.empty()) {
		collectorAgents[0]->SetMineralsReference(minerals);
		collectorAgents[0]->MoveTo(tileMap.GetPixelPosition(endX, endY));
	}

	//set collectors to move to a position
	/*for (int i = 0; i < numCollectors; ++i)
	{
		if (!collectorAgents.empty()) {
			collectorAgents[i]->MoveTo(X::Math::Vector2{ endX * 32.0f + 16.0f, endY * 32.0f + 16.0f });
		}
	}*/
}

bool GameLoop(float deltaTime)
{

	tileMap.Render();

	//agent updates
	for (auto& agent : collectorAgents)
	{
		agent->Update(deltaTime);
		agent->Render();
	}
	//resources update
	for (auto& mineral : minerals)
	{
		mineral->Render();
	}

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