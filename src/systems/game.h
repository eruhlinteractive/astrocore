#ifndef GAME
#define GAME
#include <string>
#include <raylib.h>
#include "scenetree.h"
namespace Astrocore
{
    class Game
    {
    private:
        inline static std::unique_ptr<SceneTree> sceneTree = std::unique_ptr<SceneTree>(new SceneTree());
        static void* physicsSystem; // TODO
        
        
    public:
        void Run(); // The main game loop
        Game(std::string title); // Launch with default res of 1280/720
        Game(std::string title, int windowWidth, int windowHeight);
        ~Game();
        static inline SceneTree* GetSceneTree() { return sceneTree.get();};
    };
}
#endif // !GAME