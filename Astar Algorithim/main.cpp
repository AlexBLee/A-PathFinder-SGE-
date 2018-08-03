#include "Precompiled.h"
#include "Grid.h"
#include "Game.h"

Game game;

void SGE_Initialize()
{
	game.Initialize();
}

void SGE_Terminate()
{

}

bool SGE_Update(float deltaTime)
{
	game.Update(deltaTime);
	return false;
}

void SGE_Render()
{

}
