#pragma once

class Player
{
private:
	int model;
	VECTOR pos;
	VECTOR rotate;

public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();

	void Move();
protected:

};

