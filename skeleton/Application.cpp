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

	posX = 0.0f;
	posY = 0.0f;

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
		if (CheckHitKey(KEY_INPUT_UP))
		{
			posX -= blockSize;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			posX += blockSize;
		}

		int LEN_LINE = 500.0f;
		
		

		for (int x = 0; x < 11; x++)
		{
			// 横線
			DrawLine3D(
				VGet((1200/2)-LEN_LINE, 0.0f, (1200 / 2) -LEN_LINE + x * blockSize),
				VGet((1200 / 2)+LEN_LINE, 0.0f, (1200 / 2) -LEN_LINE + x* blockSize),
				0xffffff);

			// 縦線
			DrawLine3D(
				VGet((1200 / 2) -LEN_LINE + x * blockSize, 0.0f, (1200 / 2)+LEN_LINE),
				VGet((1200 / 2) -LEN_LINE + x * blockSize, 0.0f, (1200 / 2) -LEN_LINE),
				0x00ff00);
		}

		// 中央線
		DrawLine3D(
			VGet(600.0f, LEN_LINE, (1200 / 2)),
			VGet(600.0f, 0.0f, (1200 / 2)),
			0x0000ff);


		ScreenFlip();// 画面入れ替え

		
	}

	// ソフトの終了
	DxLib_End();
}