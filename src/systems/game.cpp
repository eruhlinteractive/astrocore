#include "../../include/astrocore/systems/game.h"
using namespace Astrocore;

Game::Game(std::string title)
{   
    Debug::init();
    // Initialize window
    InitWindow(1280, 720, title.c_str());
    renderer->SetFinalTargetDimensions(1280,720);
}

Game::Game(std::string title, int windowWidth, int windowHeight) : Game(title)
{
    SetWindowSize(windowWidth, windowHeight);
    renderer->SetFinalTargetDimensions(windowWidth, windowHeight);
}

void Game::Run()
{
    while(!WindowShouldClose())
	{
        // Update
        sceneTree->GetRoot().lock()->Update(GetFrameTime());
        // TODO: Physics Update
       renderer->Render(sceneTree->drawnNodesInScene.get());
    }


    renderer.reset();
    // Cleanup
    CloseWindow();
   
}

Game::~Game()
{
    sceneTree.release();
}