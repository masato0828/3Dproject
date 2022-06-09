#pragma once


class Camera
{
private:
	VECTOR pos;
	VECTOR rotate;

public:
	Camera();
	~Camera();
	void Init();
	void Updata();
	void Draw();

	

protected:

};
