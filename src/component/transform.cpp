#include "transform.h"

using namespace Astrocore;

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
	this->position = {initialPosition.x, initialPosition.y, 0};
	this->rotation = initialRotationDegrees * PI/180.0f;
}

// Copy constructor
Transform2D::Transform2D(Transform2D* other)
{
	this->position = {other->GetPosition().x, other->GetPosition().y, 0};
	this->scale = other->GetScale();
	this->rotation = other->GetRotation();
}

Transform2D::Transform2D(Matrix transformMat)
{
	Transform2D();
	SetMatrix(transformMat);
}

void Transform2D::SetMatrix(Matrix newMat)
{
	Quaternion quat = QuaternionIdentity();
	Vector3 tempScale = {1,1,1};
	MatrixDecompose(newMat, &(this->position), &quat, &tempScale);

	this->rotation = QuaternionToEuler(quat).z;
	this->scale = {tempScale.x, tempScale.y};
}

void Transform2D::Translate(Vector2 translation)
{
	this->position = Vector3Add(position, {translation.x, translation.y, 0});
}

void Transform2D::TranslateLocal(Vector2 translation)
{
	Vector2 rotated = Vector2Transform(translation, MatrixRotateZ(rotation));
	position = Vector3Add(position, {rotated.x, rotated.y, 0});
}

void Transform2D::RotateDegrees(float rotationDelta)
{
	this->Rotate((rotationDelta * PI / 180.0f));
}

void Transform2D::Rotate(float rotationDelta)
{
	this->rotation += rotationDelta;
}

void Transform2D::Scale(Vector2 scaleDelta)
{
	scale = Vector2Multiply(scale, scaleDelta);
}

// Setters
void Transform2D::SetPosition(Vector2 newPosition)
{
	position = {newPosition.x, newPosition.y};
}

void Transform2D::SetRotationDegrees(float rotationDegrees)
{
	SetRotation(rotationDegrees * PI/180.0f );
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
	Translate(position);
}

Matrix Transform2D::GetMatrix()
{
	Matrix matToReturn = MatrixIdentity();
	matToReturn = MatrixMultiply(matToReturn, MatrixScale(scale.x, scale.y, 1));
	matToReturn = MatrixMultiply(matToReturn, MatrixRotateZ(rotation));
	matToReturn = MatrixMultiply(matToReturn, MatrixTranslate(position.x, position.y, 0));
	
	return matToReturn;

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
	return GetRotation() * 180.0f/PI;
}
