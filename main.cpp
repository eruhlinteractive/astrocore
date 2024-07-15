#include <cmath>
#include <string>
#include "src/systems/game.h"
#include "testscene.cpp"
//#include "src/systems/debug.h"

using namespace Astrocore;
int main(void)
{

	Game* myGame = new Game("Space Miner", 1280, 720);

	myGame->GetRenderer()->SetFinalTargetDimensions(420, 270);
	myGame->GetRenderer()->AddRenderTarget("basic", new RenderTarget());
	RenderTarget* rend = myGame->GetRenderer()->GetRenderTarget("basic");
	Camera2D* cam = new Camera2D();
	//cam->offset = {-210, 0};
	rend->SetRenderTargetDimensions(420, 270);
	rend->SetScreenDimensions(0,0,1);
	rend->SetActiveCamera(cam);

	std::shared_ptr<TestScene> testScn = std::shared_ptr<TestScene>(new TestScene());
	std::shared_ptr<Node> nodeShared = testScn;
	std::vector<Vector2> pts = std::vector<Vector2>();
	pts.push_back({0,3});
	pts.push_back({-7, -6});
	pts.push_back({0,14});
	pts.push_back({7,-6});

	testScn->sn = new ShapeNode( (Shape().SetLineThickness(4).FromPoints(pts)) );
	testScn->sn->GetTransform()->Scale({1,1});
	testScn->sn->GetTransform()->Translate({100, 0});
	testScn->sn->SetParent(testScn.get());
	//testScn->AddChild(testScn->sn); // TODO: This is broken
	testScn->GetTransform()->Translate({210,120});

	myGame->GetSceneTree()->SetCurrentScene(nodeShared);

	// Run the main game loop
	myGame->Run();


	delete rend;
	delete cam;
	return 0;
}
