#pragma once
#include <Dxlib.h>
class SkyDome
{
public:
	enum class STATE
	{
		NONE,
		STAY,
		FOLLOW
	};
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	
	VECTOR pos;
	VECTOR rotate;

	int model;

	VECTOR scal;

	STATE mState;

	// èÛë‘ëJà⁄
	void ChangeState(STATE state);
protected:
};

