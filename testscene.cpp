#ifndef TESTSCENE
#define TESTSCENE
#include "src/nodes/shapenode.h"
#include "src/systems/debug.h"


using namespace Astrocore;

class TestScene : public Node
{
    public:
    ShapeNode* sn;
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
        Node::Update(deltaTime);    // Base class call

        GetTransform()->Rotate(deltaTime);
        sn->GetTransform()->Rotate(-deltaTime * 2);
    }

    void Draw()
    {
        sn->Draw();
        Vector2 worldPos = GetWorldTransform().GetPosition();
        DrawRectanglePro({worldPos.x,worldPos.y,100,100}, {50,50},GetWorldTransform().GetRotationDegrees(), RED);
    }
};

#endif // !TESTSCENE