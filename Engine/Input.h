#pragma once
class Input
{
public:
	static Input* GetInstance() { return instance = (instance != nullptr) ? instance : new Input(); }

	bool leftMouseButtonDown = false;
	bool leftMouseButtonUp = false;
	bool rightMouseButtonDown = false;
	bool rightMouseButtonUp = false;

private:
	Input();
	static Input* instance;
};

