#include <Dxlib.h>
#include "Player.h"
#include "Utility.h"

Player::Player()
{
	Init();
}

Player::~Player()
{
}

void Player::Init()
{
	model = MV1LoadModel("model/Male_Casual.mv1");
	
	pos = { 0, 0, 0 };
	rotate = { 0.0f, 0.0f, 0.0f };
	MV1SetRotationXYZ(model,rotate);

	MV1SetPosition(model,pos);

	// モデルサイズセット
	MV1SetScale(model, VGet(0.25, 0.25, 0.25));

}

void Player::Update()
{
	Move();

	MV1SetRotationXYZ(model, rotate);
	MV1SetPosition(model, pos);
}

void Player::Draw()
{
	MV1DrawModel(model);

#ifdef _DEBUG
	auto color = 0xffffff;
	DrawFormatString(0,0,color,"rotate = {x:%f,y:%f,z:%f}",rotate.x, rotate.y, rotate.z);
#endif // _DEBUG

}

void Player::Move()
{
	if (CheckHitKey(KEY_INPUT_UP))
	{
		pos.z += 5;
		if (rotate.y < Utility::Deg2RadF(180.0f))
		{
			rotate.y += 0.2f;
		}
		else
		{
			rotate.y -= 0.2f;
		}
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		pos.z -= 5;
		if (rotate.y < Utility::Deg2RadF(0.0f))
		{
			rotate.y += 0.2f;
		}
		else
		{
			rotate.y -= 0.2f;
		}
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		pos.x -= 5;
		if (rotate.y < Utility::Deg2RadF(90.0f))
		{
			rotate.y += 0.2f;
		}
		else
		{
			rotate.y -= 0.2f;
		}
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		pos.x += 5;
		if (rotate.y < Utility::Deg2RadF(-90.0f))
		{
			rotate.y += 0.2f;
		}
		else
		{
			rotate.y -= 0.2f;
		}
	}


}
