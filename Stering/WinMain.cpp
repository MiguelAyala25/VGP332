#include <XEngine.h> // <> for external includes, "" for internal includes
#include <AI.h>
#include <ImGui/Inc/imgui.h>
#include "SCV.h"
using namespace AI;
AIWorld aiWorld;
std::vector<std::unique_ptr<SCV>> scvAgents;


void spawnAgent()
{
	auto& agent = scvAgents.emplace_back(std::make_unique<SCV>(aiWorld));
	agent->Load();

	const float screenWidth = X::GetScreenWidth();
	const float screenHeight = X::GetScreenHeight();

	agent->position = X::RandomVector2({ 100.0f,100.0f }, { screenWidth - 100.0f, screenHeight - 100.0f });
}

void killAgent()
{
	if (!scvAgents.empty())
	{
		auto& agent = scvAgents.back();
		agent->unLoad();
		agent.reset();
		scvAgents.pop_back();
	}
}

void GameInit()
{
	aiWorld.Initialize();

}

bool GameLoop(float deltaTime)
{
	

	ImGui::Begin("Stering", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	{
		if (ImGui::Button("SpawnAgent"))
		{
			spawnAgent();
		}

	}

	ImGui::End();

	aiWorld.Update();

	for (auto& agent: scvAgents)
	{
		agent->Update(deltaTime);
	}
	for (auto& agent : scvAgents)
	{
		agent->Render();
	}
	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);

	return quit;
}

void GameCleanup() {


}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Stering");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}