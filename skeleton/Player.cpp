#include <Dxlib.h>
#include "Player.h"
#include "Utility.h"

//Player::Player(Application* app)
//{
//	auto a = app;
//	Init();
//}

Player::~Player()
{
}

void Player::Init()
{
	model = MV1LoadModel("model/�L����/Male_Casual.mv1");
	
	pos = { 0, 0, 0 };
	rotate = { 0.0f, 0.0f, 0.0f };

	// ���f���T�C�Y�Z�b�g
	MV1SetScale(model, VGet(0.25, 0.25, 0.25));

	// �Đ����f���̃A�j���[�V�����ݒ�@0:����
	//animWalk = MV1AttachAnim(model, 3);
	anim.insert(std::make_pair(PLAYER_ANIM::IDLE, MV1AttachAnim(model, 2)));
	anim.insert(std::make_pair(PLAYER_ANIM::JUMP, MV1AttachAnim(model, 3)));


	// �A�j���[�V�����̑��Đ����Ԃ̎擾
	timeTotalAnimWalk = MV1GetAnimTotalTime(model,2);

	// �X�V�X�e�b�v
	stepAnim = 0.0f;

	// �A�j���[�V�����̍Đ����Ԃ�ݒ�
	MV1SetAttachAnimTime(model, anim.at(PLAYER_ANIM::IDLE),stepAnim);

	// �f���^�^�C��
	oldCount = std::chrono::system_clock::now();

	count = 0;
}

void Player::Update()
{

	// �f���^�^�C��
	auto nowCount = std::chrono::system_clock::now();
	deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(nowCount - oldCount).count() / 1000000000.0f;
	oldCount = nowCount;


	
	if (stepAnim > timeTotalAnimWalk)
	{
		// �A�j���[�V���������[�v
		stepAnim = 0.0f;
	}
	else
	{
		// �V�����A�j���[�V�����Đ����Ԃ��Z�b�g
		stepAnim += (deltaTime * 20.0f);
	}

	MV1SetAttachAnimTime(model,anim.at(PLAYER_ANIM::IDLE), stepAnim);

	bool isHitKey = false;
	Move(isHitKey);

	if (!isHitKey)
	{
		Camera* camera = 0;
	}
	

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

void Player::Move(bool& isMove)
{
	if (CheckHitKey(KEY_INPUT_W))
	{
		isMove = true;
		pos.z += 5;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		isMove = true;
		pos.z -= 5;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		isMove = true;
		pos.x -= 5;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		isMove = true;
		pos.x += 5;
	}


}

VECTOR Player::GetPos()
{
	return pos;
}
