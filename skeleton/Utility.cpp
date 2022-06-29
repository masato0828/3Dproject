#include <DxLib.h>
#include <math.h>
#include "Utility.h"

// ���W�A��(rad)����x(deg)
double Utility::Rad2DegD(double rad)
{
    return rad * (180.0 / DX_PI);
}

// �x(deg)���烉�W�A��(rad)
double Utility::Deg2RadD(double deg)
{
    return deg * (DX_PI / 180.0);
}

// ���W�A��(rad)����x(deg)
float Utility::Rad2DegF(float rad)
{
    return rad * (180.0f / DX_PI);
}

// �x(deg)���烉�W�A��(rad)
float Utility::Deg2RadF(float deg)
{
    return deg * (DX_PI / 180.0f);
}

// 0(0)�`2��(360�x)�͈̔͂Ɏ��߂�
double Utility::RadIn2PI(double rad)
{
    rad = fmodf(rad, DX_TWO_PI);
    if (rad < 0.0f)
    {
        rad += DX_TWO_PI;
    }

    return rad;
}

int Utility::DirNearAroundRad(float from, float to)
{
    float ret = 1.0f;
    float diff = to - from;
    if (diff >= 0.0f)
    {
        // ��r���������v���Ɉʒu����
        if (diff > DX_PI_F){
            // �ł��A180�x�ȏ㗣��Ă���̂ŁA�����v���̕����߂�
            ret = -1.0f;
        }
        else{
            // ���v���
            ret = 1.0f;
        }
    }
    else
    {
        // ��r�����������v���Ɉʒu����
        if (diff < -DX_PI_F){
            // �ł��A180�x�ȏ㗣��Ă���̂ŁA���v���̕����߂�
            ret = 1.0f;
        }
        else{
            // �����v���
            ret = -1.0f;
        }
    }

    return ret;

}