#include <cmath>
#include <string>
#include "src/systems/game.h"
#include "testscene.cpp"
//#include "src/systems/debug.h"

using namespace Astrocore;
int main(void)
{

	Game* myGame = new Game("Space Miner", 1280, 720);
	std::shared_ptr<TestScene> testScn = std::shared_ptr<TestScene>(new TestScene());
	std::shared_ptr<Node> nodeShared = testScn;
	testScn->sn = new ShapeNode( (Shape().AsRect(50,75).SetLineThickness(4)) );
	testScn->sn->GetTransform()->Translate({100, 200});
	//testScn->sn->SetParent(testScn.get());
	testScn->AddChild(testScn->sn); // TODO: This is broken
	testScn->GetTransform()->Translate({500,400});

	myGame->GetSceneTree()->SetCurrentScene(nodeShared);
	return 0;
}
