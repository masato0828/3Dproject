#pragma once
#include <chrono>
#include <map>
#include "Application.h"
#include "Camera.h"
#include <random>

enum class PLAYER_ANIM
{
	IDLE,
	JUMP,

};

class Player
{
private:

	
	//�@���X�ɉ�]�����
	static constexpr float SPEED_ROT = 10.0f;

	static constexpr float SPEED_ROT_RAD = SPEED_ROT * (DX_PI_F / 180.0f);

	// ���f���̃n���h���p
	int model;
	// �ʒu���
	VECTOR pos;
	// ��]���
	VECTOR angle;
	VECTOR angleslocal;

	std::map<PLAYER_ANIM,float > anim;

	// �A�j���[�V�����n���h���p
	float animWalk;
	//�A�j���[�V�����Đ�������
	float timeTotalAnimWalk;
	// �A�j���[�V�����X�V�p
	float stepAnim;

	float count;

	VECTOR cameraAngle;

	// �f���^�^�C��
	std::chrono::system_clock::time_point oldCount;
	float deltaTime;
public:
	//Application* app_;

	Player();
	~Player();
	void Init();
	void Update();
	void Draw();

	void Move(bool& isMove, float& rotRad);

	VECTOR GetPos();
	void SetCameraAngle(VECTOR angle);
	
protected:

};

