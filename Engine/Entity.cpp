#include "Entity.h"
Entity::Entity()
	:camera(nullptr), destinationRect({ NULL, NULL, NULL, NULL }), sourceRect({NULL, NULL, NULL, NULL }),
	texture(nullptr)
{
}
Entity::Entity(std::shared_ptr<Camera> cam)
{
	camera = cam;
	texture = camera->LoadTexture(".../GFX/DefaultTexture.png");
	position = { 0, 0 };
	centredPosition = { position.x + 15, position.y + 15 };
	sourceRect = { 0, 0, 32, 32 };
	destinationRect = { (int)position.x, (int)position.y, 64, 64 };
	radius = destinationRect.w / 2;
	id = rand() % 100000;
}

Entity::Entity(std::shared_ptr<Camera> cam, char* filePath)
{
	camera = cam;
	texture = camera->LoadTexture(filePath);
	position = { 0, 0 };
	sourceRect = { 0, 0, 32, 32 };
	destinationRect = { (int)position.x, (int)position.y, 64, 64 };
}

Entity::~Entity()
{
	SDL_DestroyTexture(texture);
}
