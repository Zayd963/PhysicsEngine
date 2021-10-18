#pragma once
#include "Entity.h"
class PlanetEntity :
    public Entity
{

public:
    PlanetEntity(std::shared_ptr<Camera> cam);
    PlanetEntity(std::shared_ptr<Camera> cam, char* filePath);

    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

