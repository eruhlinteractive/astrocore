#ifndef TRANSFORM2D
#define TRANSFORM2D
#endif // !TRANSFORM2D

#include <raymath.h>

namespace Component
{
	class Transform2D
	{
	private:
		// The transformation matrix (local)
		Matrix transformMatrix;

		// True if we need to recalculate the decompsition
		bool isDecompDirty = false;

		Vector3 position;
		Quaternion rotation;
		Vector3 scale;

		void RecalculateDecomp();

		// TODO
		void SetTransform(Vector2 position, float rotation, Vector2 scale);

	public:
		// Constructors
		Transform2D();
		Transform2D(Vector2 initialPosition, float rotation);

		// Modifiers
		void Translate(float x, float y);
		void RotateDegrees(float rotationDelta);
		void Rotate(float rotationDelta);
		void Scale(Vector2 scaleDelta);

		// Setters
		void SetPosition(float x, float y);
		void SetRotationDegrees(float rotationDegrees);
		void SetRotation(float rotation);
		void SetScale(float scaleX, float scaleY);

		// Getters
		Vector2 GetPosition();
		Vector2 GetScale();
		float GetRotation();
		float GetRotationDegrees();
	};
}
