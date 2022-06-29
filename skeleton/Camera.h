#pragma once
#include <memory>

class Player;
class Camera
{
private:
	// �J�����̍���
	float HEIGHT = 170.0f;

	// �����_����J�����܂ł�XZ����
	static constexpr float DIS_TARGET_TO_CAMERA = 300.0f;

	// �J�����̈ʒu
	VECTOR pos_;

	// �J�����̊p�x
	VECTOR angles_;


	// �J�������������
	VECTOR targetPos;
public:
	Camera();
	~Camera();
	void Init();	// ������
	void Updata();	// �X�V
	void Draw();	// �`��

	void SetTargetAngle(VECTOR pos);
	VECTOR GetAngle(void);

	void MoveCamera(void);

protected:

};
