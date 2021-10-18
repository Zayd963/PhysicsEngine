#include "Camera.h"

Camera::Camera()
{
	position.x = 640;
	position.y = 0;

	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Camera::ClearScreen()
{
	SDL_RenderClear(renderer);
}

void Camera::Render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst)
{
	SDL_RenderCopy(renderer, texture, &src, &dst);
}


void Camera::Display()
{
	SDL_RenderPresent(renderer);
}

SDL_Texture* Camera::LoadTexture(const char* filepath)
{
	SDL_Texture* temp = nullptr;
	temp = IMG_LoadTexture(renderer, filepath);

	if (temp == nullptr)
		std::cout << "Failed to load texture error: " << IMG_GetError() << std::endl;

	return temp;
}

Camera::~Camera()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}
