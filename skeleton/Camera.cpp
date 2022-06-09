#include <DxLib.h>
#include "Utility.h"
#include <math.h>
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
    pos = {740,1040,0-800};
}

void Camera::Updata()
{
    // 方向キーでカメラの座標を移動
    if (CheckHitKey(KEY_INPUT_W) == 1)
    {
        pos.y += 20.0f;
    }
    if (CheckHitKey(KEY_INPUT_S) == 1)
    {
        pos.y -= 20.0f;
    }
    if (CheckHitKey(KEY_INPUT_A) == 1)
    {
        pos.x -= 20.0f;
    }
    if (CheckHitKey(KEY_INPUT_D) == 1)
    {
        pos.x += 20.0f;
    }
}

void Camera::Draw()
{
    // カメラの位置と注視点をセット、注視点は原点
    SetCameraPositionAndTarget_UpVecY(pos, VGet(0.0f, 0.0f, 0.0f));

    DrawFormatString(0,100,0xffffff,"cameraPos x = %f:y = %f:z = %f",pos.x,pos.y,pos.z);
}


