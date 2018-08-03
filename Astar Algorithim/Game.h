#pragma once
#include "Precompiled.h"
#include "Grid.h"

class Game
{
public:
	Game();
	~Game();

	void Initialize();
	void Update(float deltaTime);
	void Render();

private:
	Grid mGrid;



};

