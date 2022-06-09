#pragma once
#include<memory>
#include "Player.h"
#include "Stage.h"
#include "Camera.h"
class Application
{
private:
	
public:
	

	Application();
	~Application();

	bool Init(void);
	void Run(void);

	std::unique_ptr<Player> player;
	std::unique_ptr<Stage> stage;
	std::unique_ptr<Camera> camera;
protected:
};

