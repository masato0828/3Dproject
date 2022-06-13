#pragma once
#include <chrono>

class Player
{
private:
	// ���f���̃n���h���p
	int model;
	// �ʒu���
	VECTOR pos;
	// ��]���
	VECTOR rotate;

	// �A�j���[�V�����n���h���p
	float animWalk;
	//�A�j���[�V�����Đ�������
	float timeTotalAnimWalk;
	// �A�j���[�V�����X�V�p
	float stepAnim;

	float count;


	// �f���^�^�C��
	std::chrono::system_clock::time_point mTickCount;
	float mDeltaTime;
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();

	void Move();
protected:

};

