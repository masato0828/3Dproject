#include <DxLib.h>
#include "Utility.h"
#include <math.h>
#include<memory>
#include "Player.h"
#include "Camera.h"


Camera::Camera()
{
	Init();
}

Camera::~Camera()
{
}

void Camera::Init()
{
    // �ʒu��񏉊�
    pos_ = { 0,580,0-800 };

    // �J�����p�x����
    // �������Ƃ�����]
    // �������Ƃ�����]
    // �������Ƃ�����]
    angles_ = {0.0f,0.0f,0.0f};
}

void Camera::Updata()
{
    float angleSpeed = 0.05f;
    float moveSpeed = 10;
    double rad = 0.0;

    // �J�����̌����ɐi��
    if (CheckHitKey(KEY_INPUT_W))
    {
        rad = Utility::Deg2RadD(0.0);
        pos_.x += sinf(angles_.y + rad) * moveSpeed;
        pos_.z += cosf(angles_.y + rad) * moveSpeed;
       
    }
    if (CheckHitKey(KEY_INPUT_S))
    {
        rad = Utility::Deg2RadD(180.0);
        pos_.x += sinf(angles_.y + rad) * moveSpeed;
        pos_.z += cosf(angles_.y + rad) * moveSpeed;
        
    }
    if (CheckHitKey(KEY_INPUT_A))
    {
        rad = Utility::Deg2RadD(-90.0);
        pos_.x += sinf(angles_.y + rad) * moveSpeed;
        pos_.z += cosf(angles_.y + rad) * moveSpeed;
       
    }
    if (CheckHitKey(KEY_INPUT_D))
    {
        rad = Utility::Deg2RadD(90.0);
        pos_.x += sinf(angles_.y + rad) * moveSpeed;
        pos_.z += cosf(angles_.y + rad) * moveSpeed;
        
    }
    if (CheckHitKey(KEY_INPUT_N))
    {
        pos_.y += moveSpeed;
    }
    if (CheckHitKey(KEY_INPUT_M))
    {
        pos_.y -= moveSpeed;
    }


    // ������ς���
    if (CheckHitKey(KEY_INPUT_DOWN))
    {
        angles_.x += angleSpeed;
    }
    if (CheckHitKey(KEY_INPUT_UP))
    {
        angles_.x -= angleSpeed;
    }
    if (CheckHitKey(KEY_INPUT_LEFT))
    {
        angles_.y -= angleSpeed;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT))
    {
        angles_.y += angleSpeed;
    }


    
}


void Camera::Draw()
{
    // �v���C���[�̏�񂪂Ȃ����
    if (player == nullptr)
    {
        // �J�����̏��̃Z�b�g
        SetCameraPositionAndAngle(pos_, angles_.x, angles_.y, angles_.z);
    }
    // �v���C���[�̏�񂪂���ꍇ
    else
    {
        // �v���C���[���S�ɂ��ăJ����������
        targetPos = player->get()->GetPos();

        // �����v���p
        float revRad = Utility::Deg2RadF(180.0f);

        // ����
        float dirX = sin(angles_.y+ revRad);
        float dirZ = cos(angles_.y+ revRad);

        // �x�N�g���i���K���j���擾
        VECTOR dir = VNorm({dirX,0.0f,dirZ});

        // �J�����̈ړ��X�s�[�h���擾
        VECTOR movePow = VScale(dir, DIS_TARGET_TO_CAMERA);

        // 
        pos_ = VAdd(targetPos,movePow);

        //
        SetCameraPositionAndTargetAndUpVec(
            pos_,
            targetPos,
            { 0.0f,1.0f,0.0f });
    }


#ifdef _DEBUG
    //�@�J�����̈ʒu���f�o�b�O
    DrawFormatString(0, 100, 0xffffff, "cameraPos x = %f:y = %f:z = %f", pos_.x, pos_.y, pos_.z);
#endif // DEBUG

    
}

void Camera::SetPlayer(std::unique_ptr<Player>* p)
{
    player = p;
}
