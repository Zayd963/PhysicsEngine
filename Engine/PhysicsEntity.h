#pragma once
#include "Entity.h"
#include "PlanetEntity.h"
class PhysicsEntity : public Entity
{
public:
	PhysicsEntity(std::shared_ptr<Camera> cam, std::shared_ptr<PlanetEntity> plan);
	PhysicsEntity(std::shared_ptr<Camera> cam, char* filePath);

	std::shared_ptr<PlanetEntity> planet = nullptr;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	~PhysicsEntity();
};

