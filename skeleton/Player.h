#pragma once
#include <chrono>
#include <map>
#include "Application.h"
#include "Camera.h"
#include <random>

enum class PLAYER_ANIM
{
	IDLE,
	JUMP,

};

class Player
{
private:

	
	//　徐々に回転する量
	static constexpr float SPEED_ROT = 10.0f;

	static constexpr float SPEED_ROT_RAD = SPEED_ROT * (DX_PI_F / 180.0f);

	// モデルのハンドル用
	int model;
	// 位置情報
	VECTOR pos;
	// 回転情報
	VECTOR angle;
	VECTOR angleslocal;

	std::map<PLAYER_ANIM,float > anim;

	// アニメーションハンドル用
	float animWalk;
	//アニメーション再生総時間
	float timeTotalAnimWalk;
	// アニメーション更新用
	float stepAnim;

	float count;

	VECTOR cameraAngle;

	// デルタタイム
	std::chrono::system_clock::time_point oldCount;
	float deltaTime;
public:
	//Application* app_;

	Player();
	~Player();
	void Init();
	void Update();
	void Draw();

	void Move(bool& isMove, float& rotRad);

	VECTOR GetPos();
	void SetCameraAngle(VECTOR angle);
	
protected:

};

