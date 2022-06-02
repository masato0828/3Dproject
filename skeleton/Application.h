#pragma once
#include<memory>

class Application
{
private:
	
public:
	

	Application();
	~Application();

	bool Init(void);
	void Run(void);


	const int blockSize = 100;
	float posX;
	float posY;
	float posZ;
	int size;


protected:
};

