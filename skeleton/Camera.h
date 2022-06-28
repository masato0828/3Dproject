#pragma once
#include <memory>

class Player;
class Camera
{
private:
	// �����_����J�����܂ł�XZ����
	static constexpr float DIS_TARGET_TO_CAMERA = 500.0f;

	// �J�����̈ʒu
	VECTOR pos_;

	// �J�����̊p�x
	VECTOR angles_;

	// �v���C���[�̃C���X�^���X�ϐ�
	std::unique_ptr<Player>* player;

	// �J�������������
	VECTOR targetPos;
public:
	Camera();
	~Camera();
	void Init();	// ������
	void Updata();	// �X�V
	void Draw();	// �`��

	void SetPlayer(std::unique_ptr<Player>* p);

protected:

};
