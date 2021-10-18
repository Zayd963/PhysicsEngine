#include <iostream>
#include "Utils.h"
#include "Camera.h"
#include "Scene.h"
#include <SDL.h>
#include "Entity.h"
#include "PhysicsEntity.h"
#include "Input.h"
#include "PlanetEntity.h"
#include <ctime>
int main(int argc, char* argv[])
{
	if (!Utils::InitSDLSystems())
		std::cout << "Failed To Init SDL" << std::endl;

	bool gameIsRunning = true;
	SDL_Event event;
	float lastTime = 0.f;

	std::shared_ptr<Camera> camera = std::make_shared<Camera>();

	Scene scene;
	scene.planet = std::make_shared<PlanetEntity>(camera);
	scene.vecEntity.push_back(scene.planet);
	unsigned seed = time(0);
	srand(seed);

	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Entity> tempEntity = std::make_shared<PhysicsEntity>(camera, scene.planet);
		float x = rand() % 1280;
		float y = rand() % 720;
		tempEntity->position = { x, y };
		tempEntity->id = rand() % 10000000;
		scene.vecEntity.push_back(tempEntity);
		
	}

	
	

	int mouseButton = 0;

	while (gameIsRunning)
	{
		

		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				gameIsRunning = false;

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (SDL_GetMouseState(nullptr, nullptr)&SDL_BUTTON(1))
				{
					mouseButton = 1;
					Input::GetInstance()->leftMouseButtonUp = false;
					Input::GetInstance()->leftMouseButtonDown = true;
				}
				if (SDL_GetMouseState(nullptr, nullptr)&SDL_BUTTON(3))
				{
					mouseButton = 4;
					Input::GetInstance()->rightMouseButtonUp = false;
					Input::GetInstance()->rightMouseButtonDown = true;
				}
			}

			if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (mouseButton == 1)
				{
					mouseButton = NULL;
					Input::GetInstance()->leftMouseButtonUp = true;
					Input::GetInstance()->leftMouseButtonDown = false;
				}
				if (mouseButton == 4)
				{
					mouseButton = NULL;
					Input::GetInstance()->rightMouseButtonUp = true;
					Input::GetInstance()->rightMouseButtonDown = false;
				}
			}
		}
			
		float time = (float)Utils::hireTimeInSeconds();
		float deltaTime = time - lastTime;
		lastTime = time;

		scene.Update(deltaTime);

		

		camera->ClearScreen();
		scene.Draw();

		for (auto pair : scene.vecCollidingPairs)
		{
			SDL_SetRenderDrawColor(camera->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(camera->renderer, pair.first->centredPosition.x, pair.first->centredPosition.y,
				pair.second->centredPosition.x, pair.second->centredPosition.y);
			SDL_SetRenderDrawColor(camera->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		}
		if (scene.selectedEntity != nullptr && scene.rightMouse)
		{
			SDL_SetRenderDrawColor(camera->renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(camera->renderer, scene.selectedEntity->centredPosition.x, 
				scene.selectedEntity->centredPosition.y, scene.mousePosition.x, scene.mousePosition.y);
			SDL_SetRenderDrawColor(camera->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		}

		

		camera->Display();

		
	}

	return 0;
}