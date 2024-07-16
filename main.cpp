#include <cmath>
#include <string>
#include "src/systems/game.h"
#include "testscene.cpp"
//#include "src/systems/debug.h"

using namespace Astrocore;
int main(void)
{

	Game* myGame = new Game("Space Miner", 1280, 720);

	myGame->GetRenderer()->SetFinalTargetDimensions(1280, 270);
	myGame->GetRenderer()->AddRenderTarget("basic", new RenderTarget());
	RenderTarget* rend = myGame->GetRenderer()->GetRenderTarget("basic");
	Camera2D* cam = new Camera2D();
	//cam->offset = {-210, 0};
	//rend->SetRenderTargetDimensions(1280, 720);
	rend->SetSourceRect({0,0,1280,720});
	rend->SetDestRect({0,0,1280,720});

	cam->offset = {1280/2.0, 720/2.0};
	cam->zoom = 1.0f;
	rend->SetActiveCamera(cam);

	std::shared_ptr<TestScene> testScn = std::shared_ptr<TestScene>(new TestScene());
	std::shared_ptr<Node> nodeShared = testScn;
	std::vector<Vector2> pts = std::vector<Vector2>();
	pts.push_back({0,3});
	pts.push_back({-7, -6});
	pts.push_back({0,14});
	pts.push_back({7,-6});

	testScn->sn = new ShapeNode( (Shape().SetLineThickness(4).FromPoints(pts).SetColor(BLUE)) );
	//testScn->sn->GetTransform()->Scale({15,15});
	//testScn->sn->GetTransform()->Translate({cam->target.x, cam->target.y});
	testScn->sn->GetTransform()->Translate({100, 0});
	//testScn->sn->SetParent(testScn.get());
	testScn->AddChild(testScn->sn); // TODO: This is broken
	//testScn->GetTransform()->Translate({0,0});

	myGame->GetSceneTree()->SetCurrentScene(nodeShared);

	// Run the main game loop
	myGame->Run();


	delete rend;
	delete cam;
	return 0;
}
