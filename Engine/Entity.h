#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Camera.h"
#include <memory>
class Entity
{
public:
	Entity();
	Entity(std::shared_ptr<Camera> cam);
	Entity(std::shared_ptr<Camera> cam, char* filePath);

	SDL_Texture* texture;
	std::shared_ptr<Camera> camera;
	Vector2 position;
	Vector2 centredPosition;
	Vector2 velocity;
	Vector2 acceleration;
	SDL_Rect sourceRect;
	SDL_Rect destinationRect;
	float radius = 30.f;
	int id = 0;
	virtual void Update(float deltaTime) = 0;

	virtual void Draw() = 0;

public:
	virtual ~Entity();
};

