#include "scenetree.h"
using namespace Astrocore;

SceneTree::SceneTree()
{
    SceneTree::created = true;
    treeRoot = std::unique_ptr<Node>(new Node("root"));
}

SceneTree::~SceneTree()
{
    treeRoot.reset();
}

std::weak_ptr<Node> SceneTree::GetRoot()
{
    return currentScene;
}

void SceneTree::SetCurrentScene(std::weak_ptr<Node> newSceneRoot)
{
    currentScene = newSceneRoot;
    newSceneRoot.lock()->OnTreeEnter(this);
}

void SceneTree::Update(float deltaTime)
{
    // Cascade the update down the tree
    treeRoot->Update(deltaTime);
}

void SceneTree::FixedUpdate(float deltaTime)
{
    // Cascade the fixed update down the tree
    treeRoot->FixedUpdate(deltaTime);
}