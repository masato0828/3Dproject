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
	model = MV1LoadModel("model/�L����/Male_Casual.mv1");
	
	pos = { 0, 0, 0 };
	rotate = { 0.0f, 0.0f, 0.0f };
	MV1SetRotationXYZ(model,rotate);

	MV1SetPosition(model,pos);

	// ���f���T�C�Y�Z�b�g
	MV1SetScale(model, VGet(0.25, 0.25, 0.25));

	// �Đ����f���̃A�j���[�V�����ݒ�@0:����
	animWalk = MV1AttachAnim(model, 1);

	// �A�j���[�V�����̑��Đ����Ԃ̎擾
	timeTotalAnimWalk = MV1GetAnimTotalTime(model,animWalk);

	// �X�V�X�e�b�v
	stepAnim = 0.0f;

	// �A�j���[�V�����̍Đ����Ԃ�ݒ�
	MV1SetAttachAnimTime(model,animWalk,stepAnim);

	// �f���^�^�C��
	mTickCount = std::chrono::system_clock::now();

	count = 0;
}

void Player::Update()
{

	// �f���^�^�C��
	auto tickCount = std::chrono::system_clock::now();
	mDeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(tickCount - mTickCount).count() / 1000000000.0f;
	mTickCount = tickCount;


	// �V�����A�j���[�V�����Đ����Ԃ��Z�b�g
	stepAnim += (mDeltaTime * 20.0f);
	if (stepAnim > timeTotalAnimWalk)
	{
		// �A�j���[�V���������[�v
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
