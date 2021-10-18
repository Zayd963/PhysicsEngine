#include "PlanetEntity.h"

PlanetEntity::PlanetEntity(std::shared_ptr<Camera> cam)
{
	camera = cam;
	texture = camera->LoadTexture("../GFX/Star.png");
	position = { 640, 480 };
	
	velocity = { 0, 0 };
	acceleration = { 0, 0 };
	sourceRect = { 0, 0, 32, 32 };

	destinationRect = { (int)position.x, (int)position.y, 128, 128 };
	radius = destinationRect.w / 2;
	centredPosition.x = position.x + radius;
	centredPosition.y = position.y + radius;
}

void PlanetEntity::Update(float deltaTime)
{

}

void PlanetEntity::Draw()
{
	camera->Render(texture, sourceRect, destinationRect);
}
