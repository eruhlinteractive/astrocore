#include <cmath>
#include <string>
#include "src/systems/game.h"
#include "testscene.cpp"
//#include "src/systems/debug.h"

using namespace Astrocore;
int main(void)
{

	Game* myGame = new Game("Space Miner", 1280, 720);

	myGame->GetRenderer()->SetFinalTargetDimensions(420,270);
	myGame->GetRenderer()->AddRenderTarget("basic", new RenderTarget());
	RenderTarget* rend = myGame->GetRenderer()->GetRenderTarget("basic");

	std::shared_ptr<TestScene> testScn = std::shared_ptr<TestScene>(new TestScene());
	std::shared_ptr<Node> nodeShared = testScn;
	std::vector<Vector2> pts = std::vector<Vector2>();
	pts.push_back({0,3});
	pts.push_back({-7, -6});
	pts.push_back({0,14});
	pts.push_back({7,-6});

	testScn->sn = new ShapeNode( (Shape().SetLineThickness(4).FromPoints(pts)) );
	testScn->sn->GetTransform()->Scale({5,5});
	testScn->sn->GetTransform()->Translate({100, 200});
	testScn->sn->SetParent(testScn.get());
	//testScn->AddChild(testScn->sn); // TODO: This is broken
	testScn->GetTransform()->Translate({500,400});

	myGame->GetSceneTree()->SetCurrentScene(nodeShared);

	// Run the main game loop
	myGame->Run();
	return 0;
}
