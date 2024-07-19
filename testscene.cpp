#ifndef TESTSCENE
#define TESTSCENE
#include "src/nodes/shapenode.h"
#include "src/systems/debug.h"
#include "src/systems/input/input.h"


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
        
        Input::AddBinding("moveUp", InputAction(KEYBOARD, KEY_W));
        Input::AddBinding("moveDown", InputAction(KEYBOARD, KEY_S));
        Input::AddBinding("moveLeft", InputAction(KEYBOARD, KEY_A));
        Input::AddBinding("moveRight", InputAction(KEYBOARD, KEY_D));
        // parentNode.GetTransform()->RotateDegrees(45);
        // t2D.Translate(200, 200);
    }

    void Update(float deltaTime)
    {
        Node::Update(deltaTime);    // Base class call
        //GetTransform()->Rotate(deltaTime);
        if(Input::IsActionHeld("moveUp"))
        {
            sn->GetTransform()->TranslateLocal({0, deltaTime * 100.0f});
        }
        else if(Input::IsActionHeld("moveDown"))
        {
            sn->GetTransform()->TranslateLocal({0, -deltaTime * 100.0f});
        }

        if(Input::IsActionHeld("moveLeft"))
        {
            sn->GetTransform()->Rotate(deltaTime);
        }
        else if(Input::IsActionHeld("moveRight"))
        {
            sn->GetTransform()->Rotate(-deltaTime);
        }
        
        //DBG_LOG(std::to_string(Input::IsActionHeld("moveDown")));
        //sn->GetTransform()->Rotate(-deltaTime);
    }

    void Draw()
    {
        sn->Draw();
        Vector2 worldPos = GetWorldTransform().GetPosition();
        DrawRectanglePro({worldPos.x,worldPos.y,100,100}, {50,50},GetWorldTransform().GetRotationDegrees(), RED);
    }
};

#endif // !TESTSCENE