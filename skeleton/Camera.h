#pragma once
#include <memory>

class Player;
class Camera
{
private:
	// 注視点からカメラまでのXZ距離
	static constexpr float DIS_TARGET_TO_CAMERA = 500.0f;

	// カメラの位置
	VECTOR pos_;

	// カメラの角度
	VECTOR angles_;

	// プレイヤーのインスタンス変数
	std::unique_ptr<Player>* player;

	// カメラが見るもの
	VECTOR targetPos;
public:
	Camera();
	~Camera();
	void Init();	// 初期化
	void Updata();	// 更新
	void Draw();	// 描画

	void SetPlayer(std::unique_ptr<Player>* p);

protected:

};
