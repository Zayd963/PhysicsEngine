#include "Scene.h"
#include "PhysicsEntity.h"
#include "Input.h"
Scene::Scene()
	:mouseX(0), mouseY(0)
{
}

void Scene::Update(float deltaTime)
{
	vecCollidingPairs.clear();
	
	auto mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	mousePoint = { mouseX, mouseY };
	mousePosition = { (float)mouseX, (float)mouseY };
	
	

	if (Input::GetInstance()->leftMouseButtonDown)
	{
		rightMouse = false;
		for (auto ent : vecEntity)
		{
			if (EntityIsInPoint(ent, mousePoint))
			{
				selectedEntity = ent.get();
				selectedEntity->velocity = { 0, 0 };
				break;
			}
		}
	}

	if (Input::GetInstance()->leftMouseButtonUp && !rightMouse)
	{
		if (selectedEntity != nullptr)
		{
			selectedEntity = nullptr;
		}
	}

	if (Input::GetInstance()->rightMouseButtonDown)
	{
		rightMouse = true;
		for (auto ent : vecEntity)
		{
			if (EntityIsInPoint(ent, mousePoint))
			{
				selectedEntity = ent.get();
				break;
			}
		}
	}

	

	if (Input::GetInstance()->rightMouseButtonUp && rightMouse)
	{
		if (selectedEntity != nullptr)
		{
			selectedEntity->velocity = (selectedEntity->position - mousePosition) * 5;
			selectedEntity = nullptr;
		}
	}

	if (selectedEntity != nullptr && !rightMouse)
	{
		selectedEntity->position = { mousePosition.x - selectedEntity->radius, mousePosition.y - selectedEntity->radius };
		selectedEntity = nullptr;
	}

	/*StaticCollisionResolution();

	DynamicCollisionResolution();*/

	for (auto ent : vecEntity)
	{
		ent->Update(deltaTime);
	}

	
}

bool Scene::EntityIsInPoint(std::shared_ptr<Entity> ent, SDL_Point& point)
{
	return ((ent->centredPosition.x - point.x) * (ent->centredPosition.x - point.x) + (ent->centredPosition.y - point.y) * (ent->centredPosition.y - point.y) < (ent->radius) * (ent->radius));
}

bool Scene::CircleVSCircleCollision(std::shared_ptr<Entity> ent1, std::shared_ptr<Entity> ent2)
{
	return fabs((ent1->position.x - ent2->position.x) * ( ent1->position.x - ent2->position.x) + (ent1->position.y - ent2->position.y) * (ent1->position.y - ent2->position.y) <= (ent1->radius + ent2->radius) * (ent1->radius + ent2->radius));
}

void Scene::StaticCollisionResolution()
{
	for (auto ent : vecEntity)
	{
		for (auto target : vecEntity)
		{
			if (ent->id != target->id && ent != planet && target != planet)
			{
				if (CircleVSCircleCollision(ent, target))
				{
					vecCollidingPairs.push_back({ ent, target });

					Vector2 difference = ent->position - target->position;

					float distanceBetweenBalls = sqrt((difference.x * difference.x) + (difference.y * difference.y));

					float displacementRequired = 0.5f * (distanceBetweenBalls - ent->radius - target->radius);

					ent->position -= (difference * displacementRequired) / distanceBetweenBalls;
					target->position += (difference * displacementRequired) / distanceBetweenBalls;
				}
			}
		}
	}
}

void Scene::DynamicCollisionResolution()
{
	for (auto pair : vecCollidingPairs)
	{
		std::shared_ptr<Entity> ent1 = pair.first;
		std::shared_ptr<Entity> ent2 = pair.second;
		
		//Vector Between Entitys (ie normal)
		Vector2 normal = (ent2->position - ent1->position).Normalize();
		//Normal of normal (ie tangent)
		Vector2 tangent = { -normal.y, normal.x };
		//Dot product along tangent for ent1
		float dotProductTangent1 = ent1->velocity.x * tangent.x + ent1->velocity.y * tangent.y;
		//Dot product along tangent for ent2
		float dotProductTangent2 = ent2->velocity.x * tangent.x + ent2->velocity.y * tangent.y;

		// Dot Product along normal for ent1
		float dotProductNormal1 = ent1->velocity.x * normal.x + ent1->velocity.y * normal.y;
		// Dot Product along normal for ent2
		float dotProductNormal2 = ent2->velocity.x * normal.x + ent2->velocity.y * normal.y;

		// Conservation of momentum for ent1
		float momentum1 = (dotProductNormal1 * (1 - 1) + 2.0f * 1 * dotProductNormal2) / (1 + 1);
		// Conservation of momentum for ent2
		float momentum2 = (dotProductNormal2 * (1 - 1) + 2.0f * 1 * dotProductNormal1) / (1 + 1);

		// Update ent velocities
		ent1->velocity = (tangent * dotProductTangent1) + (normal * momentum1);
		ent2->velocity = (tangent * dotProductTangent2) + (normal * momentum2);
	}
}

void Scene::Draw()
{
	for (auto ent : vecEntity)
	{
		ent->Draw();
	}
}

Scene::~Scene()
{
	
}
