#ifndef SCENETREE
#define SCENETREE
#include "../nodes/node.h"
namespace Astrocore
{
    class SceneTree
    {
        private:
        // The root of the entire tree
        std::unique_ptr<Node> treeRoot;
        inline static bool created = false;    // Track if we've already created an instance
        // The base node of the current scene 
        // NOTE: Using weak ptrs here because we don't want to explicitly own the object
        std::weak_ptr<Node> currentScene;

    public:
        SceneTree();
        ~SceneTree(); 
        std::weak_ptr<Node> GetRoot();
        
        // Set's the current scene WITHOUT deleting the current scene
        void SetCurrentScene(std::weak_ptr<Node> newSceneRoot);
        // Set's the current scene, deleting the old scene
        void SwapCurrentScene(std::weak_ptr<Node> newSceneRoot);
        
        void Update(float deltaTime);
        void FixedUpdate(float deltaTime);
    };
}
#endif // !SCENETREE