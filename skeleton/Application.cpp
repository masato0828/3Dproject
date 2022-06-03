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
		
		

		for (int x = 0; x < 21; x++)
		{
			// 横線
			DrawLine3D(
				VGet(-LEN_LINE, 0.0f,-LEN_LINE + x * blockSize),
				VGet(LEN_LINE, 0.0f, -LEN_LINE + x* blockSize),
				0xffffff);

			// 縦線
			DrawLine3D(
				VGet( -LEN_LINE + x * blockSize, 0.0f, +LEN_LINE),
				VGet(-LEN_LINE + x * blockSize, 0.0f,  -LEN_LINE),
				0x00ff00);
		}

		// 中央線
		DrawLine3D(
			VGet(0.0f, LEN_LINE, 0.0f),
			VGet(0.0f, 0.0f, 0.0f),
			0x0000ff);


		ScreenFlip();// 画面入れ替え

		
	}

	// ソフトの終了
	DxLib_End();
}