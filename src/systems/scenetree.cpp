#include "../../include/astrocore/systems/scenetree.h"
using namespace Astrocore;

SceneTree::SceneTree()
{
    SceneTree::created = true;
    treeRoot = std::unique_ptr<TreeNode>(new TreeNode());
}

SceneTree::~SceneTree()
{
    treeRoot.reset();
}

std::weak_ptr<TreeNode> SceneTree::GetRoot()
{
    return currentScene;
}

void SceneTree::SetCurrentScene(std::weak_ptr<TreeNode> newSceneRoot)
{
    this->currentScene = newSceneRoot;
    RegisterToTree(newSceneRoot);
}

void SceneTree::RegisterToTree(std::weak_ptr<TreeNode> nodeToRegister)
{
    drawnNodesInScene->push_back(nodeToRegister);
    nodeToRegister.lock()->EnterTree(this);
}

void SceneTree::DeRegisterToTree(std::weak_ptr<TreeNode> nodeToDeRegister)
{
    //drawnNodesInScene->erase();
    // TODO: Find in tree and push 
}