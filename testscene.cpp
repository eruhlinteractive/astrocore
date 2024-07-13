#ifndef TESTSCENE
#define TESTSCENE
#include "src/nodes/node.h"
#include "src/systems/debug.h"

using namespace Astrocore;
class TestScene : public Node
{
    void OnTreeEnter(SceneTree *tree)
    {
        Node::OnTreeEnter(tree);
        DBG_LOG("Hello from inside the new scene!");

        // parentNode.GetTransform()->RotateDegrees(45);
        // t2D.Translate(200, 200);
    }

    void Update(float deltaTime)
    {

    }
};

#endif // !TESTSCENE