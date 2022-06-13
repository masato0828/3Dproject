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
	model = MV1LoadModel("model/キャラ/Male_Casual.mv1");
	
	pos = { 0, 0, 0 };
	rotate = { 0.0f, 0.0f, 0.0f };
	MV1SetRotationXYZ(model,rotate);

	MV1SetPosition(model,pos);

	// モデルサイズセット
	MV1SetScale(model, VGet(0.25, 0.25, 0.25));

	// 再生モデルのアニメーション設定　0:成功
	animWalk = MV1AttachAnim(model, 1);

	// アニメーションの総再生時間の取得
	timeTotalAnimWalk = MV1GetAnimTotalTime(model,animWalk);

	// 更新ステップ
	stepAnim = 0.0f;

	// アニメーションの再生時間を設定
	MV1SetAttachAnimTime(model,animWalk,stepAnim);

	// デルタタイム
	mTickCount = std::chrono::system_clock::now();

	count = 0;
}

void Player::Update()
{

	// デルタタイム
	auto tickCount = std::chrono::system_clock::now();
	mDeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(tickCount - mTickCount).count() / 1000000000.0f;
	mTickCount = tickCount;


	// 新しいアニメーション再生時間をセット
	stepAnim += (mDeltaTime * 20.0f);
	if (stepAnim > timeTotalAnimWalk)
	{
		// アニメーションをループ
		stepAnim = 0.0f;
	}

	MV1SetAttachAnimTime(model,animWalk,stepAnim);


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
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		pos.z -= 5;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		pos.x -= 5;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		pos.x += 5;
	}


}
