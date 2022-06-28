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
    // 位置情報初期
    pos_ = { 0,580,0-800 };

    // カメラ角度初期
    // ｘを軸とした回転
    // ｙを軸とした回転
    // ｚを軸とした回転
    angles_ = {0.0f,0.0f,0.0f};
}

void Camera::Updata()
{
    float angleSpeed = 0.05f;
    float moveSpeed = 10;
    double rad = 0.0;

    // カメラの向きに進む
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


    // 向きを変える
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
    // プレイヤーの情報がなければ
    if (player == nullptr)
    {
        // カメラの情報のセット
        SetCameraPositionAndAngle(pos_, angles_.x, angles_.y, angles_.z);
    }
    // プレイヤーの情報がある場合
    else
    {
        // プレイヤー中心にしてカメラが動く
        targetPos = player->get()->GetPos();

        // 方向計測用
        float revRad = Utility::Deg2RadF(180.0f);

        // 方向
        float dirX = sin(angles_.y+ revRad);
        float dirZ = cos(angles_.y+ revRad);

        // ベクトル（正規化）を取得
        VECTOR dir = VNorm({dirX,0.0f,dirZ});

        // カメラの移動スピードを取得
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
    //　カメラの位置情報デバッグ
    DrawFormatString(0, 100, 0xffffff, "cameraPos x = %f:y = %f:z = %f", pos_.x, pos_.y, pos_.z);
#endif // DEBUG

    
}

void Camera::SetPlayer(std::unique_ptr<Player>* p)
{
    player = p;
}
