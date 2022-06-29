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
    //pos_ = { 0,580,0-800 };
    pos_ = { 0,180,0-800 };

    // �J�����p�x����
    // �������Ƃ�����]
    // �������Ƃ�����]
    // �������Ƃ�����]
    angles_ = { Utility::Deg2RadF(15.0f),0.0f,0.0f};
    targetPos = {0,0,0};
}

void Camera::Updata()
{
    MoveCamera();


    // �v���C���[�̏�񂪂Ȃ����
    // �J�����̏��̃Z�b�g
    // �����v���p
    float revRad = Utility::Deg2RadF(180.0f);

    // ����
    float dirX = sin(angles_.y + revRad);
    float dirZ = cos(angles_.y + revRad);

    // �x�N�g���i���K���j���擾
    VECTOR dir = VNorm({ dirX,0.0f,dirZ });

    // �J�����̈ړ��X�s�[�h���擾
    VECTOR movePow = VScale(dir, DIS_TARGET_TO_CAMERA);
    movePow.y += pos_.y;
    // 
    pos_ = VAdd(targetPos, movePow);



    // �v���C���[�𒍎��_�ɂ���
    {
        //
        SetCameraPositionAndTargetAndUpVec(
            pos_,
            targetPos,
            { 0.0f,1.0f,0.0f });

        SetCameraPositionAndAngle(pos_, angles_.x, angles_.y, angles_.z);
    }
}


void Camera::Draw()
{
#ifdef _DEBUG
    //�@�J�����̈ʒu���f�o�b�O
    DrawFormatString(0, 100, 0xffffff, "cameraPos x = %f:y = %f:z = %f", pos_.x, pos_.y, pos_.z);
    DrawFormatString(0, 200, 0xffffff, "cameraAngles x = %f:y = %f:z = %f", Utility::Rad2DegF(-180.0f), angles_.y, angles_.z);
#endif // DEBUG

    
}

void Camera::SetTargetAngle(VECTOR pos)
{
    targetPos = pos;
}

VECTOR Camera::GetAngle()
{
    return angles_;
}

void Camera::MoveCamera(void)
{
    float angleSpeed = Utility::Deg2RadF(5.0f);
    float moveSpeed = 10;
    double rad = 0.0;

    //// �J�����̌����ɐi��
    //if (CheckHitKey(KEY_INPUT_W))
    //{
    //    rad = Utility::Deg2RadD(0.0);
    //    pos_.x += sinf(angles_.y + rad) * moveSpeed;
    //    pos_.z += cosf(angles_.y + rad) * moveSpeed;
    //   
    //}
    //if (CheckHitKey(KEY_INPUT_S))
    //{
    //    rad = Utility::Deg2RadD(180.0);
    //    pos_.x += sinf(angles_.y + rad) * moveSpeed;
    //    pos_.z += cosf(angles_.y + rad) * moveSpeed;
    //    
    //}
    //if (CheckHitKey(KEY_INPUT_A))
    //{
    //    rad = Utility::Deg2RadD(-90.0);
    //    pos_.x += sinf(angles_.y + rad) * moveSpeed;
    //    pos_.z += cosf(angles_.y + rad) * moveSpeed;
    //   
    //}
    //if (CheckHitKey(KEY_INPUT_D))
    //{
    //    rad = Utility::Deg2RadD(90.0);
    //    pos_.x += sinf(angles_.y + rad) * moveSpeed;
    //    pos_.z += cosf(angles_.y + rad) * moveSpeed;
    //    
    //}

    // �v���C���[���S�ɂ��ăJ��������������



    if (CheckHitKey(KEY_INPUT_N))
    {
        pos_.y += moveSpeed;
    }
    if (CheckHitKey(KEY_INPUT_M))
    {
        pos_.y -= moveSpeed;
    }


    // �J������]
    // ����45�x�܂�
    if ((CheckHitKey(KEY_INPUT_DOWN)) && (angles_.x < Utility::Deg2RadF(45.0f)))
    {

        if (pos_.y < 170)
        {
            angles_.x += angleSpeed;
            pos_.y += 20;
        }
    }
    // ���-45�x�܂�
    if ((CheckHitKey(KEY_INPUT_UP)) && (angles_.x > Utility::Deg2RadF(-180.0f)))
    {

        if (pos_.y > 0)
        {
            angles_.x -= angleSpeed;
            pos_.y -= 20;
        }
    }
    if (CheckHitKey(KEY_INPUT_LEFT))
    {
        // �͈͐����Ȃ��J������]
        angles_.y -= angleSpeed;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT))
    {
        // �͈͐����Ȃ��J������]
        angles_.y += angleSpeed;
    }
}
