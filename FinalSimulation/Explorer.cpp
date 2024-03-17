#include "Explorer.h"

void Explorer::Initialize(const X::Math::Vector2& spawnPosition)
{
	mTextureId = X::LoadTexture("interceptor_01.png");
	position = spawnPosition;
	//save this to be able to return
	Spawnposition = spawnPosition;
}

void Explorer::Update(float deltaTime)
{
	if (isMoving) {
		FollowPath(deltaTime);
	}
}

void Explorer::Wander()
{
	//seed
	static bool initialized = false;
	if (!initialized) {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		initialized = true;
	}

	//Posible directions 
	std::vector<std::pair<int, int>> directions = {
	  {0, 1},
	  {1, 0}, 
	  {0, -1}, 
	  {-1, 0}, 
	  {-1, -1},
	  {1, -1}, 
	  {-1, 1}, 
	  {1, 1}   
	};

	auto [currentTileX, currentTileY] = tileMap.WorldToGrid(position.x, position.y);
	bool found = false;
	for (int i = 0; i < directions.size() && !found; ++i) {
		// Selecciona una dirección aleatoria.
		int dirIndex = std::rand() % directions.size();
		auto [dx, dy] = directions[dirIndex];

		int newX = currentTileX + dx;
		int newY = currentTileY + dy;

		// Verifica si el tile es caminable y no es el tile actual.
		if (tileMap.IsCommonTile(newX, newY) && (dx != 0 || dy != 0)) {
			// Calcula la nueva posición del mundo basada en el tile seleccionado.
			X::Math::Vector2 newWorldPos = tileMap.GridToWorld(newX, newY);

			// Inicia el movimiento hacia el nuevo destino.
			MoveTo(newWorldPos);
			found = true;
		}	
	}
}

void Explorer::FollowPath(float deltaTime)
{
	timeSinceLastMove += deltaTime;

	if (timeSinceLastMove >= .5f) {
		if (currentPathIndex < currentPath.size()) {
			const X::Math::Vector2& nextPoint = currentPath[currentPathIndex];
			position = nextPoint;
			++currentPathIndex;

			if (currentPathIndex >= currentPath.size()) {
				isMoving = false;
				Wander();
			}
			timeSinceLastMove = 0.0f;
		}
	}
}