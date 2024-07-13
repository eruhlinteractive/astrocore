#include "game.h"

using namespace Astrocore;

Game::Game(std::string title)
{
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
        sceneTree->Update(GetFrameTime());
        // Physics Update


        // Render
        // TODO: Placeholder
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    // Cleanup
    CloseWindow();
}

Game::~Game()
{
    sceneTree.release();
}