#include <cmath>
#include <string>
#include "src/systems/game.h"
#include "testscene.cpp"
//#include "src/systems/debug.h"

using namespace Astrocore;
int main(void)
{

	
	Game* myGame = new Game("Space Miner", 1280, 720);
	//SetWindowState(FLAG_WINDOW_RESIZABLE);
	myGame->GetRenderer()->SetFinalTargetDimensions(480, 270);
	
	Camera2D* cam = new Camera2D();
	myGame->GetRenderer()->GetRenderTarget("basic")->SetActiveCamera(cam);
	cam->offset = {480/2.0f, 270/2.0f };
	cam->zoom = 1.0f;

	std::shared_ptr<TestScene> testScn = std::shared_ptr<TestScene>(new TestScene());
	std::shared_ptr<Node> nodeShared = testScn;
	std::vector<Vector2> pts = std::vector<Vector2>();
	pts.push_back({7,-6});
	pts.push_back({0,14});
	pts.push_back({-7, -6});
	pts.push_back({0,3});
	

	testScn->sn = new ShapeNode( Shape().SetLineThickness(4).FromPoints(pts).SetColor(BLUE).SetFilled(true) );
	testScn->sn->GetTransform()->Scale({2, 2});
	//testScn->sn->GetTransform()->Translate({cam->target.x, cam->target.y});
	testScn->sn->GetTransform()->Translate({100, 0});
	//testScn->sn->SetParent(testScn.get());
	testScn->AddChild(testScn->sn); // TODO: This is broken

	myGame->GetSceneTree()->SetCurrentScene(nodeShared);

	// Run the main game loop
	myGame->Run();

	delete cam;
	return 0;
}
