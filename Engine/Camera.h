#pragma once
#include "Vector2.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
class Camera
{
public:
	Camera();
	void ClearScreen();
	void Render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst);
	void Display();
	SDL_Texture* LoadTexture(const char* filepath);
	inline Vector2 GetPosition() { return position; }
	inline SDL_Window* GetWindow() { return window; }
	~Camera();



	Vector2 position;
	SDL_Window* window;
	SDL_Renderer* renderer;

	
};

