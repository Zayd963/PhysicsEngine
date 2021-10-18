#pragma once
#include "Entity.h"
#include <vector>
#include <memory>
#include "Vector2.h"
#include "PlanetEntity.h"
class Scene
{
public:
	Scene();

	std::vector<std::shared_ptr<Entity>> vecEntity;
	std::vector<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>> vecCollidingPairs;
	Entity* selectedEntity = nullptr;
	std::shared_ptr<PlanetEntity> planet = nullptr;
	SDL_Event event;
	int mouseX, mouseY;
	bool rightMouse = false;
	SDL_Point mousePoint;
	Vector2 mousePosition;

	void Update(float deltaTime);

	bool EntityIsInPoint(std::shared_ptr<Entity> ent, SDL_Point& point);

	bool CircleVSCircleCollision(std::shared_ptr<Entity> ent1, std::shared_ptr<Entity> ent2);

	void StaticCollisionResolution();

	void DynamicCollisionResolution();

	void Draw();

	~Scene();
	
};

