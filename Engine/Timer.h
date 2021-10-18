#pragma once
#include <SDL.h>
class Timer
{
public:
	Timer(float _time = 0.0f)
		:time(_time)
	{

	}

	float GetTimeInMilliseconds() { return (float)SDL_GetTicks(); }
	float GetTimeInSeconds() { return (float)SDL_GetTicks() * 0.001f; }

private:
	float time;
};

