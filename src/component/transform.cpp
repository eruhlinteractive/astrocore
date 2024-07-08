#include <raymath.h>
#include "transform.h"
#include <cmath>

using namespace Component;

// NOTE: Per the OpenGL docs, transforms should be done in the order: scale, rotate, translate

Transform2D::Transform2D()
{
	position = {0,0};
	rotation = QuaternionIdentity();
	scale = {1,1};
	transformMatrix = MatrixIdentity();
	RecalculateDecomp();
}

Transform2D::Transform2D(Vector2 initialPosition, float initialRotationDegrees)
{
	Transform2D();
	transformMatrix = MatrixMultiply(transformMatrix,
									 MatrixTranslate(initialPosition.x, initialPosition.y, 0));
	transformMatrix = MatrixMultiply(transformMatrix, MatrixRotateZ(initialRotationDegrees * (PI / 180)));
	RecalculateDecomp();
}

void Transform2D::Translate(float x, float y)
{
	// Reverse the rotation, apply the translation, then re-rotate
	float currentRot = GetRotation();
	//transformMatrix = MatrixMultiply(transformMatrix, MatrixRotateZ(-currentRot) );
	Rotate(-currentRot);
	transformMatrix = MatrixMultiply(transformMatrix, MatrixTranslate(x, y, 0));
	//transformMatrix = MatrixMultiply(transformMatrix, MatrixRotateZ(currentRot));
	Rotate(currentRot);
	//position = {x + position.x, y + position.y, 0};
	isDecompDirty = true;
}

void Transform2D::RotateDegrees(float rotationDelta)
{
	Rotate(rotationDelta * (PI / 180.0f));
}

void Transform2D::Rotate(float rotationDelta)
{
	Vector2 pos = GetPosition();
	Vector2 currentScale = GetScale();
	Matrix offsetTranslation = MatrixTranslate(-pos.x, -pos.y, 0);
	//Matrix offsetScale = MatrixScale(1.0 - currentScale.x, 1.0 - currentScale.y, 1);
	transformMatrix = MatrixMultiply(transformMatrix, offsetTranslation);
	//transformMatrix = MatrixMultiply(transformMatrix, offsetScale);
	
	transformMatrix = MatrixMultiply(transformMatrix, MatrixRotateZ(rotationDelta));
	//transformMatrix = MatrixMultiply(transformMatrix, MatrixScale(currentScale.x, currentScale.y, 1));
	transformMatrix = MatrixMultiply(transformMatrix, MatrixTranslate(pos.x, pos.y, 0));
	isDecompDirty = true;
}

void Transform2D::Scale(Vector2 scaleDelta)
{
	// TODO: Validate that scale is positive
	transformMatrix = MatrixMultiply(transformMatrix, MatrixScale(scaleDelta.x, scaleDelta.y, 0));
	isDecompDirty = true;
}

// Setters
void Transform2D::SetPosition(float x, float y)
{
	if(isDecompDirty)
	{
		RecalculateDecomp();
	}

	Vector2 position = GetPosition();
	Translate(-position.x, -position.y);
	Translate(x,y);
	//SetTransform({x,y}, GetRotation(), GetScale());
}

void Transform2D::SetRotationDegrees(float rotationDegrees)
{
	SetRotation(rotationDegrees * (PI/180) );
}

void Transform2D::SetRotation(float rotation)
{
	if(isDecompDirty)
	{
		RecalculateDecomp();
	}
	float delta = rotation - GetRotation();
	Rotate(delta);
	//SetTransform(GetPosition(), rotation, GetScale());
}

void Transform2D::SetScale(float scaleX, float scaleY)
{
	Vector2 posPrev = GetPosition();
	float rotPrev = GetRotation();
	transformMatrix = MatrixIdentity();
	transformMatrix = MatrixMultiply(transformMatrix, MatrixScale(scaleX, scaleY, 1));
	Rotate(rotPrev);
	isDecompDirty = true;
}

void Transform2D::RecalculateDecomp()
{
	MatrixDecompose(transformMatrix, &position, &rotation, &scale);
	isDecompDirty = false;
}

void Transform2D::SetTransform(Vector2 position, float rotation, Vector2 scale)
{
	transformMatrix = MatrixIdentity();
	Scale(scale);
	Rotate(rotation);
	Translate(position.x, position.y);
	RecalculateDecomp();
}

Vector2 Transform2D::GetPosition()
{
	if(isDecompDirty)
	{
		RecalculateDecomp();
	}
	return {position.x, position.y};
}

Vector2 Transform2D::GetScale()
{
	if(isDecompDirty)
	{
		RecalculateDecomp();
	}

	return {scale.x, scale.y};
}

float Transform2D::GetRotation()
{
	if(isDecompDirty)
	{
		RecalculateDecomp();
	}

	return QuaternionToEuler(rotation).z;
}

float Transform2D::GetRotationDegrees()
{
	return GetRotation() * (180/PI);
}