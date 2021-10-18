#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(std::shared_ptr<Camera> cam, std::shared_ptr<PlanetEntity> plan)
{
	camera = cam;
	texture = camera->LoadTexture("../GFX/DefaultTexture.png");
	position = { 0, 0 };
	velocity = { 0, 0 };
	acceleration = { 0, 0 };
	sourceRect = { 0, 0, 32, 32 };
	planet = plan;
	destinationRect = { (int)position.x, (int)position.y, 64, 64 };
	radius = destinationRect.w / 2;
	
}

PhysicsEntity::PhysicsEntity(std::shared_ptr<Camera> cam, char* filePath)
{
	camera = cam;
	texture = camera->LoadTexture(filePath);
	position = { 0, 0 };
	velocity = { 0, 0 };
	acceleration = { 0, 0 };
	radius = 30.f;
	sourceRect = { 0, 0, 32, 32 };
	destinationRect = { (int)position.x, (int)position.y, 64, 64 };
}

void PhysicsEntity::Update(float deltaTime)
{
	
	Vector2 drag = (velocity * -1) * 0.8;
	Vector2 gravity = { 0, 0 };
	Vector2 differenceToPlanet = (centredPosition - planet->centredPosition).Normalize() * 200;
	acceleration = ((differenceToPlanet * -1) + drag);


	if (fabs(velocity.x * velocity.x + velocity.y * velocity.y) < 1.f)
	{
		velocity.x = 0;
		velocity.y = 0;
	}

	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;
	centredPosition.x = position.x + radius;
	centredPosition.y = position.y + radius;
	destinationRect.x = (int)position.x;
	destinationRect.y = (int)position.y;
	radius = destinationRect.w / 2;
}

void PhysicsEntity::Draw()
{

	if (position.x > 1280 - radius)
		position.x = 0;
	if (position.x < 0)
		position.x = 1280 - radius;
	if (position.y > 720)
		position.y = 0 + radius;
	if (position.y < 0)
		position.y = 720 - radius;

	camera->Render(texture, sourceRect, destinationRect);
	
	
	Vector2 vec = velocity.Normalize() * radius;
	Vector2 drawVector = (centredPosition + vec);
	/*drawVector = drawVector.Normalize();
	drawVector = drawVector * radius;*/

	if (velocity.Mag() <= 1.0f)
	{
		SDL_SetRenderDrawColor(camera->renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(camera->renderer, centredPosition.x, centredPosition.y, centredPosition.x + radius, centredPosition.y);
		SDL_SetRenderDrawColor(camera->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

		SDL_SetRenderDrawColor(camera->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(camera->renderer, &destinationRect);
		SDL_SetRenderDrawColor(camera->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	}
	else
	{
		SDL_SetRenderDrawColor(camera->renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(camera->renderer, centredPosition.x, centredPosition.y, drawVector.x, drawVector.y);
		SDL_SetRenderDrawColor(camera->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

		SDL_SetRenderDrawColor(camera->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(camera->renderer, &destinationRect);
		SDL_SetRenderDrawColor(camera->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	}

}

PhysicsEntity::~PhysicsEntity()
{
	SDL_DestroyTexture(texture);
}
