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
	SetGraphMode(1200, 720, 32);

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



	return true;
}

void Application::Run(void)
{
	// ESCキーを押すとプログラム終了
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{


		ClsDrawScreen();// 画面の状態の初期化


		ScreenFlip();// 画面入れ替え

		
	}

	// ソフトの終了
	DxLib_End();
}