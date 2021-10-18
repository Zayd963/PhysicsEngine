#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#define LOG(x) std::cout << x << std::endl;

namespace Utils
{
	bool InitSDLSystems()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			std::cout << "SDL Failed to init" << std::endl;
			return false;
		}

		if (!IMG_Init(IMG_INIT_PNG))
		{
			std::cout << "IMG Failed To Init" << std::endl;
			return false;
		}

		return true;
	}

	enum class State
	{
		DEBUGGING = 1,
		PLAYTESTING = 0
	};

	inline float hireTimeInSeconds()
	{
		float t = SDL_GetTicks();
		t *= 0.001f;

		return t;
	}
}