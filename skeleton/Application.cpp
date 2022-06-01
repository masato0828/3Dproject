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

		//DrawLine(0, 0, 100, 0, 0xffffff,true);
		//DrawBox(0,0,100,100,0xffffff,true);
		

		int LEN_LINE = 5000.0f;
		for (int x = 0; x < 1111; x++)
		{
			DrawLine3D(
				VGet(-LEN_LINE, 0.0f, -LEN_LINE + x * 100),
				VGet(LEN_LINE, 0.0f, LEN_LINE + x*100),
				0xffffff);

			DrawLine3D(
				VGet(-LEN_LINE + x * 100, 0.0f, LEN_LINE),
				VGet(-LEN_LINE + x * 100, 0.0f, -LEN_LINE),
				0x00ff00);
		}

		DrawLine3D(
			VGet(0.0f, LEN_LINE, 0.0f),
			VGet(0.0f, -LEN_LINE, 0.0f),
			0x0000ff);

		ScreenFlip();// 画面入れ替え

		
	}

	// ソフトの終了
	DxLib_End();
}