#pragma once

class Utility
{
public:
	// ���W�A��(rad)����x(deg)
	static double Rad2DegD(double rad);

	// �x(deg)���烉�W�A��(rad)
	static double Deg2RadD(double deg);

	// ���W�A��(rad)����x(deg)
	static float Rad2DegF(float rad);

	// �x(deg)���烉�W�A��(rad)
	static float Deg2RadF(float deg);

	// 0(0)�`2��(360�x)�͈̔͂Ɏ��߂�
	double RadIn2PI(double rad);

	// ��]�����Ȃ����̉�]�������擾����(���v���:1�A�����v���:-1)
	int DirNearAroundRad(float from, float to);
private:

protected:

};
