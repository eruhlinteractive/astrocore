#ifndef SCENETREE
#define SCENETREE

#include <vector>
#include <memory>
#include "../nodes/treenode.h"

namespace Astrocore
{
    class SceneTree
    {
        friend class Node;
        friend class Game;
        private:
        // The root of the entire tree
        std::unique_ptr<TreeNode> treeRoot;
        inline static bool created = false;    // Track if we've already created an instance

        // Track all nodes currently in the scene
        std::unique_ptr<std::vector<std::weak_ptr<TreeNode>>> drawnNodesInScene = 
            std::unique_ptr<std::vector<std::weak_ptr<TreeNode>>>(new std::vector<std::weak_ptr<TreeNode>>());
        
        // The base node of the current scene 
        // NOTE: Using weak ptrs here because we don't want to explicitly own the object
        std::weak_ptr<TreeNode> currentScene;

        std::weak_ptr<void> currentCamera;

    public:
        SceneTree();
        ~SceneTree(); 
        std::weak_ptr<TreeNode> GetRoot();
        
        // Set's the current scene WITHOUT deleting the current scene
        void SetCurrentScene(std::weak_ptr<TreeNode> newSceneRoot);
        // Set's the current scene, deleting the old scene
        void SwapCurrentScene(std::weak_ptr<TreeNode> newSceneRoot);
        void Update(float deltaTime);
        void FixedUpdate(float deltaTime);
        void RegisterToTree(std::weak_ptr<TreeNode> nodeToRegister);
        void DeRegisterToTree(std::weak_ptr<TreeNode> nodeToDeRegister);
    };
}
#endif // !SCENETREE