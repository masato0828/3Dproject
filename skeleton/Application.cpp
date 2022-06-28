#include <DxLib.h>
#include "Application.h"

Application::Application()
{
}

Application::~Application()
{
}

bool Application::Init(void)
{
	// 画面の大きさ
	SetGraphMode(1200, 800, 32);

	/// ウィンドウモード、フルスクリーンモードの変更を行う
	/// <true>ウィンドウモード
	/// <false>フルスクリーン
	ChangeWindowMode(true);

	// Dxlibの初期化
	if (DxLib_Init() == -1)
	{
		// errorが起きたら終了
		return false;
	}

	// カメラ初期値が左下のため初期値を真ん中にする
	SetCameraPositionAndTargetAndUpVec(VGet(0, 200, -400)/*視点*/, VGet(0, 0, 0)/*見てる場所*/, VGet(0, 1, 0)/*釘を打たないとくるくる回る*/);
	//player = std::make_unique<Player>(this);
	stage = std::make_unique<Stage>();
	camera = std::make_unique<Camera>();
	camera->SetPlayer(player);

	return true;
}

void Application::Run(void)
{
	// ESCキーを押すとプログラム終了
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//player->Update();
		stage->Update();
		camera->Updata();
		

		ClsDrawScreen();// 画面の状態の初期化
		
		stage->Draw();
		//player->Draw();
		camera->Draw();
		
		

		ScreenFlip();// 画面入れ替え

		
	}

	// ソフトの終了
	DxLib_End();
}

Camera* Application::GetCamera()
{
	return camera.get();
}
