#include "UpdateLogic.h"

using namespace s3dge;

float horizontalAngle = 0;
float verticalAngle = 0;

void UpdateCamera(Camera& camera, const Vector3& position, const Vector2& displacement)
{
	const float speed = 0.1f;
	const float mouseSpeed = 3.0f;

	Vector3 cameraPosition(position);

	horizontalAngle += mouseSpeed * displacement.x;
	verticalAngle -= mouseSpeed * displacement.y;

	if (verticalAngle > 1.57f)
		verticalAngle = 1.57f;
	if (verticalAngle < -1.57f)
		verticalAngle = -1.57f;

	Vector3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), -cos(verticalAngle) * cos(horizontalAngle));
	Vector3 right(-(float)sin(horizontalAngle - 3.14 / 2.0f), 0, (float)cos(horizontalAngle - 3.14 / 2.0f));
	Vector3 up((Vector3::GetCrossProduct(right, direction)));

	if (InputManager::KeyDown(S3_KEY_W))
		cameraPosition += speed * direction;
	if (InputManager::KeyDown(S3_KEY_S))
		cameraPosition -= speed * direction;
	if (InputManager::KeyDown(S3_KEY_A))
		cameraPosition -= speed * right;
	if (InputManager::KeyDown(S3_KEY_D))
		cameraPosition += speed * right;
	if (InputManager::KeyDown(S3_KEY_Q))
		cameraPosition -= speed * up;
	if (InputManager::KeyDown(S3_KEY_E))
		cameraPosition += speed * up;
	if (InputManager::KeyDown(S3_KEY_SPACE))
	{
		horizontalAngle = 0;
		verticalAngle = 0;
	}
	if (InputManager::KeyDown(S3_KEY_MWUP))
		camera.SetFOV(camera.GetFOV() - 1);
	if (InputManager::KeyDown(S3_KEY_MWDOWN))
		camera.SetFOV(camera.GetFOV() + 1);
	if (InputManager::KeyDown(S3_KEY_MMB))
		camera.SetFOV(45);

	camera.SetPosition(cameraPosition);
	camera.SetViewDirection(direction);
	camera.SetUp(up);
}
