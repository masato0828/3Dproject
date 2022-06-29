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
	angle = { 0.0f, 0.0f, 0.0f };
	angleslocal = { 0.0f,Utility::Deg2RadF(180.0f),0.0f };

	//モデルの角度を設定
	VECTOR angles = angle;
	angles.x += angleslocal.x;
	angles.y += angleslocal.y;
	angles.z += angleslocal.z;
	MV1SetRotationXYZ(model, angles);


	// モデルサイズセット
	MV1SetScale(model, VGet(0.25, 0.25, 0.25));

	// 再生モデルのアニメーション設定　0:成功
	//animWalk = MV1AttachAnim(model, 3);
	anim.insert(std::make_pair(PLAYER_ANIM::IDLE, MV1AttachAnim(model, 2)));
	anim.insert(std::make_pair(PLAYER_ANIM::JUMP, MV1AttachAnim(model, 3)));


	// アニメーションの総再生時間の取得
	timeTotalAnimWalk = MV1GetAnimTotalTime(model,2);

	// 更新ステップ
	stepAnim = 0.0f;

	// アニメーションの再生時間を設定
	MV1SetAttachAnimTime(model, anim.at(PLAYER_ANIM::IDLE),stepAnim);

	// デルタタイム
	oldCount = std::chrono::system_clock::now();

	count = 0;
}

void Player::Update()
{

	// デルタタイム
	auto nowCount = std::chrono::system_clock::now();
	deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(nowCount - oldCount).count() / 1000000000.0f;
	oldCount = nowCount;


	
	if (stepAnim > timeTotalAnimWalk)
	{
		// アニメーションをループ
		stepAnim = 0.0f;
	}
	else
	{
		// 新しいアニメーション再生時間をセット
		stepAnim += (deltaTime * 20.0f);
	}

	MV1SetAttachAnimTime(model,anim.at(PLAYER_ANIM::JUMP), stepAnim);

	float movePow = 5.0f;
	float moveHPow = movePow / 2.0f;
	float rad = 0.0f;
	// 操作キー判定
	bool isHitMove = false;;

	// 回転したい角度
	float rotRad = 0.0f;;


	Move(isHitMove, rotRad);

	if (isHitMove)
	{
		// カメラが向いている方向に移動する
		pos.x += sinf(cameraAngle.y + rotRad) * moveHPow;
		pos.z += cosf(cameraAngle.y + rotRad) * moveHPow;

		// 移動方向にキャラクターの角度を徐々に変える
		float radUnitAnglesY = angle.y;
		float radMoveAnglesY = cameraAngle.y + rotRad;
		Utility utility;
		radMoveAnglesY = utility.RadIn2PI(radMoveAnglesY);

		// 回転量が少ない方の回転方向を取得する(時計回り：1、反時計回り:-1)
		float aroundDir = utility.DirNearAroundRad(radUnitAnglesY, radMoveAnglesY);

		float diff = radMoveAnglesY - radUnitAnglesY;
		float absDiff = abs(diff);

		if (0.1f > absDiff)
		{
			// しきい値以内である
			angle.y = radMoveAnglesY;
		}
		else
		{
			// 回転量を加える
			angle.y += (SPEED_ROT_RAD * aroundDir);
		}

		// プレイヤーがくるくる回らないように固定する
		angle.y = utility.RadIn2PI(angle.y);
	}
	

	//モデルの角度を設定
	VECTOR angles = angle;
	angles.x += angleslocal.x;
	angles.y += angleslocal.y;
	angles.z += angleslocal.z;

	// モデル座標の設定

	MV1SetRotationXYZ(model, angles);
	MV1SetPosition(model, pos);


}

void Player::Draw()
{
	MV1DrawModel(model);

#ifdef _DEBUG
	auto color = 0xffffff;
	DrawFormatString(0,0,color,"rotate = {x:%f,y:%f,z:%f}",angle.x, angle.y, angle.z);
#endif // _DEBUG

}

void Player::Move(bool& isMove,float& rotRad)
{
	if (CheckHitKey(KEY_INPUT_W))
	{
		isMove = true;
		rotRad = Utility::Deg2RadF(0.0f);
		
	}
	else if (CheckHitKey(KEY_INPUT_S))
	{
		isMove = true;
		rotRad = Utility::Deg2RadF(180.0f);
	} 
	else if (CheckHitKey(KEY_INPUT_A))
	{
		isMove = true;
		rotRad = Utility::Deg2RadF(-90.0f);
	}
	else if (CheckHitKey(KEY_INPUT_D))
	{
		isMove = true;
		rotRad = Utility::Deg2RadF(90.0f);
	}

	

}

VECTOR Player::GetPos()
{
	return pos;
}

void Player::SetCameraAngle(VECTOR angle)
{
	cameraAngle = angle;
}
