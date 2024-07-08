#include <cmath>
#include <raylib.h>
#include "src/component/transform.h"
#include <iostream>
#include <fstream>
#include <string>

int main(void)
{
	// Basic window setup
	int posX = 0;
	InitWindow(800, 450, "Asteroids In C");
	
	Component::Transform2D t2D = Component::Transform2D();
	Component::Transform2D t2 = Component::Transform2D();
	
	Rectangle rectOne = Rectangle();
	rectOne.height = 100;
	rectOne.width = 50;
	t2D.Scale({1.0f, 0.5f});

	Rectangle rectTwo = Rectangle();
	rectTwo.height = 100;
	rectTwo.width = 100;
	//rectOne.width = 100 * t2D.GetScale().x;
	//rectOne.height = 100 * t2D.GetScale().y;

	//t2.SetScale(1, 0.5);
	//rectTwo.width = 100 * t2.GetScale().x;
	//t2D.Translate(100, 50);
	SetTargetFPS(60);
	float rot = 0;
	while(!WindowShouldClose())
	{
		float vec = sin(GetTime()) * 20 * GetFrameTime();
		//std::cout << vec << std::endl;

		//Vector2 pos1 = t2D.GetPosition();
		float amountToRot = 1;
		//rot = rot + amountToRot;
		//t2D.SetPosition(pos1.x, pos1.y + vec);
		
		t2D.RotateDegrees(amountToRot);
		t2D.Translate(0, vec);
		
		std::cout << t2D.GetScale().x << std::endl;
		
		Vector2 pos1 = t2D.GetPosition();
		Vector2 scale1 = t2D.GetScale();
		rectOne.x = pos1.x + 100;
		rectOne.y = pos1.y + 100;
		rectOne.height = 100 * scale1.y;
		rectOne.width = 100 * scale1.x;
		// Red
		t2.Translate(0, vec);
		float newRot = t2D.GetRotationDegrees() + amountToRot;
		t2.SetRotationDegrees(newRot);
		
		Vector2 pos2 = t2.GetPosition();
		rectTwo.x = 400 + pos2.x;
		rectTwo.y = 100 + pos2.y;
		
		//t2D.Translate(0, vec);
		//t2D.SetPosition(0, vec);
		BeginDrawing();
		ClearBackground(RAYWHITE);
		//std::cout << t2.GetRotationDegrees() << std::endl;
		DrawRectanglePro(rectOne, {50,50}, t2D.GetRotationDegrees(), BLUE);
		DrawRectanglePro(rectTwo, {50,50}, t2.GetRotationDegrees(), RED);
		
		DrawLine(400, 0, 400, 450, ORANGE);
		DrawLine(100, 0, 100, 450, ORANGE);
		
		DrawCircle(rectTwo.x,rectTwo.y,4, GREEN);
		DrawCircle(rectOne.x,rectOne.y,4, GREEN);
		EndDrawing(); 
	}
	CloseWindow();
	return 0;
}
