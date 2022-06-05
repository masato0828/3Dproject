#include <DxLib.h>
#include "Utility.h"

double Utility::Rad2DegD(double rad)
{
    return rad * (180.0/DX_PI);
}

double Utility::Deg2RadD(double deg)
{
    return deg * (DX_PI / 180.0);
}

float Utility::Rad2DegF(float rad)
{
    return rad * (180.0f / DX_PI);
}

float Utility::Deg2RadF(float deg)
{
    return deg * (DX_PI / 180.0f);
}
