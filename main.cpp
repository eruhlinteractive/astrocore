#include <cmath>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include "src/nodes/node.h"

using namespace Astrocore;
int main(void)
{
	// Basic window setup
	int posX = 0;
	InitWindow(800, 450, "Asteroids In C");
	
	Rectangle rectOne = Rectangle();
	rectOne.height = 100;
	rectOne.width = 100;

	Rectangle rectTwo = Rectangle();
	rectTwo.height = 100;
	rectTwo.width = 100;


	Node parentNode = Node();
	Node childNode = Node();

	parentNode.name = "parentNode";
	childNode.name = "childNode";

	parentNode.AddChild(&childNode);
	childNode.GetTransform()->Translate({200, 0});

	Transform2D t2D = new Transform2D();

	//rectOne.width = 100 * t2D.GetScale().x;
	//rectOne.height = 100 * t2D.GetScale().y;

	//t2.SetScale(1, 0.5);
	//rectTwo.width = 100 * t2.GetScale().x;
	//t2D.Translate(100, 50);
	parentNode.GetTransform()->Translate({250, 200});
	SetTargetFPS(60);
	float rot = 0;

	//parentNode.GetTransform()->RotateDegrees(45);
	//t2D.Translate(200, 200);
	while(!WindowShouldClose())
	{
		float vec = sin(GetTime()) * 20 * GetFrameTime();
		//std::cout << vec << std::endl;
		parentNode.GetTransform()->RotateDegrees(45.0 * GetFrameTime());
		//childNode.GetTransform()->RotateDegrees(-45.0 * GetFrameTime());

		//Vector2 pos1 = t2D.GetPosition();
		float amountToRot = 1;
		parentNode.GetTransform()->TranslateLocal({vec,0});
		
		//t2D.RotateDegrees(amountToRot *vec);
		//parentNode.GetTransform()->Translate(0, vec);
		Vector2 childPos = childNode.GetWorldTransform().GetPosition();
		//Vector3 newChild = Vector3Transform({0, 0, 0}, t2D.GetMatrix());
		//newChild = Vector3Transform(newChild, MatrixRotateZ(t2D.GetRotation()));
		rectTwo.x = childPos.x;
		rectTwo.y = childPos.y;

		Vector2 parentPos = parentNode.GetWorldTransform().GetPosition();
		rectOne.x = parentPos.x;
		rectOne.y = parentPos.y;

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawRectanglePro(rectOne, {50,50}, parentNode.GetWorldTransform().GetRotationDegrees(), BLUE);
		DrawRectanglePro(rectTwo, {50,50}, childNode.GetWorldTransform().GetRotationDegrees(), RED);
		
		DrawLine(400, 0, 400, 450, ORANGE);
		DrawLine(100, 0, 100, 450, ORANGE);
		
		DrawCircle(rectTwo.x,rectTwo.y,4, GREEN);
		DrawCircle(rectOne.x,rectOne.y,4, GREEN);
		EndDrawing(); 
	}
	CloseWindow();
	return 0;
}
