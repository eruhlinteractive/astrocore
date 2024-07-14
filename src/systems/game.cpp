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
        // TODO: Update scene tree, run physics/rendering 

        // Update
        sceneTree->GetRoot().lock()->Update(GetFrameTime());
        // Physics Update


        // Render
       renderer->Render(sceneTree->drawnNodesInScene.get());

       DBG_LOG("End Frame");
    }

    // Cleanup
    CloseWindow();
}

Game::~Game()
{
    sceneTree.release();
}