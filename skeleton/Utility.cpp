#include <DxLib.h>
#include <math.h>
#include "Utility.h"

// ラジアン(rad)から度(deg)
double Utility::Rad2DegD(double rad)
{
    return rad * (180.0 / DX_PI);
}

// 度(deg)からラジアン(rad)
double Utility::Deg2RadD(double deg)
{
    return deg * (DX_PI / 180.0);
}

// ラジアン(rad)から度(deg)
float Utility::Rad2DegF(float rad)
{
    return rad * (180.0f / DX_PI);
}

// 度(deg)からラジアン(rad)
float Utility::Deg2RadF(float deg)
{
    return deg * (DX_PI / 180.0f);
}

// 0(0)～2π(360度)の範囲に収める
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
        // 比較元よりも時計回りに位置する
        if (diff > DX_PI_F){
            // でも、180度以上離れているので、反時計回りの方が近い
            ret = -1.0f;
        }
        else{
            // 時計回り
            ret = 1.0f;
        }
    }
    else
    {
        // 比較元よりも反時計回りに位置する
        if (diff < -DX_PI_F){
            // でも、180度以上離れているので、時計回りの方が近い
            ret = 1.0f;
        }
        else{
            // 反時計回り
            ret = -1.0f;
        }
    }

    return ret;

}