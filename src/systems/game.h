#ifndef GAME
#define GAME
#include <string>
#include "scenetree.h"
#include "renderer.h"

namespace Astrocore
{
    class Game
    {
    private:
        inline static std::unique_ptr<SceneTree> sceneTree = std::unique_ptr<SceneTree>(new SceneTree());
        static void* physicsSystem; // TODO
        inline static std::unique_ptr<Renderer> renderer = std::unique_ptr<Renderer>(new Renderer()); 
        
        
    public:
        void Run(); // The main game loop
        Game(std::string title); // Launch with default res of 1280/720
        Game(std::string title, int windowWidth, int windowHeight);
        ~Game();
        static inline SceneTree* GetSceneTree() { return sceneTree.get();};
    };
}
#endif // !GAME