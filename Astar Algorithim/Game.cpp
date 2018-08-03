#include "Precompiled.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Initialize()
{
	mGrid.InitializeArray();

}

void Game::Update(float deltaTime)
{
	Render();
}

void Game::Render()
{
	mGrid.Render();
}
