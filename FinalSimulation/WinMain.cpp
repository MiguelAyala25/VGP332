#include "TileMap.h"
#include <XEngine.h> // <> for external includes, "" for internal includes
#include <ImGui/Inc/imgui.h>
#include <AI.h>

//agents
#include "Collector.h"
#include "Explorer.h"

//resources 
#include "Mineral.h"

using namespace AI;

AIWorld aiWorld;
X::Math::Vector2 destination = X::Math::Vector2::Zero();

//collectors 
std::vector<std::unique_ptr<Collector>> collectorAgents;
int numCollectors = 1;

//explorers
std::vector<std::unique_ptr<Explorer>> explorerAgents;
int numExplorers = 1;

//Resoucers
std::vector<std::unique_ptr<Mineral>> minerals;
int mineralNum = 10;

//tileMaps
TileMap tileMap;
X::TextureId textureId;
X::Math::Vector2 position;
Path path;

int endX = 12;
int endY = 11;

int endX1 = 7;
int endY1 = 12;

X::Math::Vector2 TestPosition = (endX,endY);

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
			//collectors
			auto& collector = collectorAgents.emplace_back(std::make_unique<Collector>(aiWorld, tileMap));
			collector->SetMineralsReference(minerals);
			collector->Initialize(baseTilesPositions[randomIndex]);

			//explorers
			auto& explorer = explorerAgents.emplace_back(std::make_unique<Explorer>(aiWorld, tileMap));
			explorer->Initialize(baseTilesPositions[randomIndex]);

			baseTilesPositions.erase(baseTilesPositions.begin() + randomIndex);
		}
	}
}

void InitalizeResources()
{
	auto& mineral = minerals.emplace_back(std::make_unique<Mineral>(aiWorld));
	mineral->Initialize(tileMap.GetPixelPosition(endX, 15));

	/*std::vector<X::Math::Vector2> regularTilesPositions;

	//Gets the "non-base tiles"
	for (int y = 0; y < tileMap.getRows(); ++y) {
		for (int x = 0; x < tileMap.getColumns(); ++x) {
			if (tileMap.IsCommonTile(x, y) == true) {
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

	tileMap.InitializeTileWeights();

	InitializeAgents();
	InitalizeResources();

	if (!collectorAgents.empty() && !minerals.empty()) {
		auto mineralPosition = minerals.front()->GetPosition();
		collectorAgents.front()->SetTargetPosition(mineralPosition);
	}


	if (!explorerAgents.empty() && !minerals.empty()) {
		//auto mineralPosition = minerals.front()->GetPosition();
		explorerAgents.front()->SetTargetPosition(TestPosition);
	}

}

bool GameLoop(float deltaTime)
{

	tileMap.Render(false);

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