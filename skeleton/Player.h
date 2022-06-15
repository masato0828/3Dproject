#pragma once
#include <chrono>
#include <map>

enum class PLAYER_ANIM
{
	IDLE,
	JUMP,

};

class Player
{
private:
	// ���f���̃n���h���p
	int model;
	// �ʒu���
	VECTOR pos;
	// ��]���
	VECTOR rotate;

	std::map<PLAYER_ANIM,float > anim;

	// �A�j���[�V�����n���h���p
	float animWalk;
	//�A�j���[�V�����Đ�������
	float timeTotalAnimWalk;
	// �A�j���[�V�����X�V�p
	float stepAnim;

	float count;


	// �f���^�^�C��
	std::chrono::system_clock::time_point oldCount;
	float deltaTime;
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();

	void Move();
protected:

};

