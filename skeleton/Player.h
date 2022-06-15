#pragma once
#include <chrono>
#include <map>

enum class PLAYER_ANIM
{
	IDLE,
	JUMP,

};

class Player
{
private:
	// モデルのハンドル用
	int model;
	// 位置情報
	VECTOR pos;
	// 回転情報
	VECTOR rotate;

	std::map<PLAYER_ANIM,float > anim;

	// アニメーションハンドル用
	float animWalk;
	//アニメーション再生総時間
	float timeTotalAnimWalk;
	// アニメーション更新用
	float stepAnim;

	float count;


	// デルタタイム
	std::chrono::system_clock::time_point oldCount;
	float deltaTime;
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();

	void Move();
protected:

};

