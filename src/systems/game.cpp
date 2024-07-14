#include "game.h"
using namespace Astrocore;

Game::Game(std::string title)
{   
    Debug::init();
    // Initialize window
    InitWindow(1280, 720, title.c_str());
}

Game::Game(std::string title, int windowWidth, int windowHeight) : Game(title)
{
    SetWindowSize(windowWidth, windowHeight);
}

void Game::Run()
{
    while(!WindowShouldClose())
	{
        // Update
        sceneTree->GetRoot().lock()->Update(GetFrameTime());
        // Physics Update
        // TODO:
        // Render
       renderer->Render(sceneTree->drawnNodesInScene.get());
    }

    // Cleanup
    CloseWindow();
}

Game::~Game()
{
    sceneTree.release();
}