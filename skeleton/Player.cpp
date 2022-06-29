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
	angle = { 0.0f, 0.0f, 0.0f };
	angleslocal = { 0.0f,Utility::Deg2RadF(180.0f),0.0f };

	//���f���̊p�x��ݒ�
	VECTOR angles = angle;
	angles.x += angleslocal.x;
	angles.y += angleslocal.y;
	angles.z += angleslocal.z;
	MV1SetRotationXYZ(model, angles);


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

	MV1SetAttachAnimTime(model,anim.at(PLAYER_ANIM::JUMP), stepAnim);

	float movePow = 5.0f;
	float moveHPow = movePow / 2.0f;
	float rad = 0.0f;
	// ����L�[����
	bool isHitMove = false;;

	// ��]�������p�x
	float rotRad = 0.0f;;


	Move(isHitMove, rotRad);

	if (isHitMove)
	{
		// �J�����������Ă�������Ɉړ�����
		pos.x += sinf(cameraAngle.y + rotRad) * moveHPow;
		pos.z += cosf(cameraAngle.y + rotRad) * moveHPow;

		// �ړ������ɃL�����N�^�[�̊p�x�����X�ɕς���
		float radUnitAnglesY = angle.y;
		float radMoveAnglesY = cameraAngle.y + rotRad;
		Utility utility;
		radMoveAnglesY = utility.RadIn2PI(radMoveAnglesY);

		// ��]�ʂ����Ȃ����̉�]�������擾����(���v���F1�A�����v���:-1)
		float aroundDir = utility.DirNearAroundRad(radUnitAnglesY, radMoveAnglesY);

		float diff = radMoveAnglesY - radUnitAnglesY;
		float absDiff = abs(diff);

		if (0.1f > absDiff)
		{
			// �������l�ȓ��ł���
			angle.y = radMoveAnglesY;
		}
		else
		{
			// ��]�ʂ�������
			angle.y += (SPEED_ROT_RAD * aroundDir);
		}

		// �v���C���[�����邭����Ȃ��悤�ɌŒ肷��
		angle.y = utility.RadIn2PI(angle.y);
	}
	

	//���f���̊p�x��ݒ�
	VECTOR angles = angle;
	angles.x += angleslocal.x;
	angles.y += angleslocal.y;
	angles.z += angleslocal.z;

	// ���f�����W�̐ݒ�

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
