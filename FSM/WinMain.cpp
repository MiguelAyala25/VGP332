
#include <XEngine.h> // <> for external includes, "" for internal includes
#include <ImGui/Inc/imgui.h>
#include "Miner.h"
#include "Pilot.h"
Miner miner;
Pilot pilot;
void GameInit()
{
	//miner.Initialize();
	pilot.Initialize();
}

bool GameLoop(float deltaTime)
{
	
	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		//miner.Update(deltaTime);
		pilot.Update(deltaTime);
	}

	ImGui::Begin("FSM", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		//miner.DebugUI();
		pilot.DebugUI();
	ImGui::End();


	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);

	return quit;
}

void GameCleanup()
{
	//miner.Terminate();
	pilot.Terminate();
}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("FSM");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}