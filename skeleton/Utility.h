#pragma once

class Utility
{
public:
	// ラジアン(rad)から度(deg)
	static double Rad2DegD(double rad);

	// 度(deg)からラジアン(rad)
	static double Deg2RadD(double deg);

	// ラジアン(rad)から度(deg)
	static float Rad2DegF(float rad);

	// 度(deg)からラジアン(rad)
	static float Deg2RadF(float deg);

	// 0(0)～2π(360度)の範囲に収める
	double RadIn2PI(double rad);

	// 回転が少ない方の回転向きを取得する(時計回り:1、反時計回り:-1)
	int DirNearAroundRad(float from, float to);
private:

protected:

};
