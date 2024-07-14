#ifndef TESTSCENE
#define TESTSCENE
#include "src/nodes/node.h"
#include "src/systems/debug.h"


using namespace Astrocore;
class TestScene : public Node
{
    void EnterTree(SceneTree *tree)
    {
        //Node::OnTreeEnter(tree);
        DBG_WARN("Hello from inside the new scene!");
        this->isDrawn = true;
        name = "testScene";
        // parentNode.GetTransform()->RotateDegrees(45);
        // t2D.Translate(200, 200);
    }

    void Update(float deltaTime)
    {
        GetTransform()->Rotate(deltaTime);
    }

    void Draw()
    {
        DrawRectanglePro({100,100,100,100}, {50,50},GetWorldTransform().GetRotationDegrees(), RED);
    }
};

#endif // !TESTSCENE