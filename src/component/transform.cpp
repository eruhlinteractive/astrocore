#include <raymath.h>
#include "transform.h"
#include <cmath>

using namespace Component;

// NOTE: Per the OpenGL docs, transforms should be done in the order: scale, rotate, translate

Transform2D::Transform2D()
{
	position = {0,0};
	rotation = 0;
	scale = {1,1};
}

Transform2D::Transform2D(Vector2 initialPosition, float initialRotationDegrees)
{
	Transform2D();
	position = {initialPosition.x, initialPosition.y, 0};
	rotation = initialRotationDegrees * (PI/180);
}

void Transform2D::Translate(float x, float y)
{
	position = Vector3Add(position, {x,y,0});
}

void Transform2D::RotateDegrees(float rotationDelta)
{
	Rotate(rotationDelta * (PI / 180.0f));
}

void Transform2D::Rotate(float rotationDelta)
{
	rotation += rotationDelta;
}

void Transform2D::Scale(Vector2 scaleDelta)
{
	scale = Vector2Multiply(scale, scaleDelta);
}

// Setters
void Transform2D::SetPosition(float x, float y)
{
	position = {x, y};
}

void Transform2D::SetRotationDegrees(float rotationDegrees)
{
	SetRotation(rotationDegrees * (PI/180) );
}

void Transform2D::SetRotation(float rotation)
{
	this->rotation = rotation;
}

void Transform2D::SetScale(float scaleX, float scaleY)
{
	scale = {scaleX, scaleY};
}


void Transform2D::SetTransform(Vector2 position, float rotation, Vector2 scale)
{
	Scale(scale);
	Rotate(rotation);
	Translate(position.x, position.y);
}

Vector2 Transform2D::GetPosition()
{
	return {position.x, position.y};
}

Vector2 Transform2D::GetScale()
{
	return {scale.x, scale.y};
}

float Transform2D::GetRotation()
{
	return rotation;
}

float Transform2D::GetRotationDegrees()
{
	return GetRotation() * (180/PI);
}