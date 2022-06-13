#pragma once


class Camera
{
private:
	VECTOR pos_;
	VECTOR angles_;


public:
	Camera();
	~Camera();
	void Init();
	void Updata();
	void Draw();

	

protected:

};
