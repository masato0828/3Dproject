#pragma once
#include <memory>

class Player;
class Camera
{
private:
	// カメラの高さ
	float HEIGHT = 170.0f;

	// 注視点からカメラまでのXZ距離
	static constexpr float DIS_TARGET_TO_CAMERA = 300.0f;

	// カメラの位置
	VECTOR pos_;

	// カメラの角度
	VECTOR angles_;


	// カメラが見るもの
	VECTOR targetPos;
public:
	Camera();
	~Camera();
	void Init();	// 初期化
	void Updata();	// 更新
	void Draw();	// 描画

	void SetTargetAngle(VECTOR pos);
	VECTOR GetAngle(void);

	void MoveCamera(void);

protected:

};
