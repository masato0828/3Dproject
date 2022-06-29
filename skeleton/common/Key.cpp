#include "Key.h"

// 現在のキーを押しているフレーム数
int nowKeyPressFrame[KeyKindMax];

// ひとつ前のキーを押しているフレーム数
int oldKeyPressFrame[KeyKindMax];

void KeyInit(void)
{
	// 配列の初期化
	for (int i = 0; i < KeyKindMax; i++)
	{
		nowKeyPressFrame[i] = 0;
		oldKeyPressFrame[i] = 0;
	}
}

void KeyUpdate(void)
{
	// 一時的に保持するキー情報
	char keyState[KeyKindMax];

	// すべてのキー情報を一度に取得
	GetHitKeyStateAll(&keyState[0]);

	// キー情報を更新
	for (int i = 0; i < KeyKindMax; i++)
	{
		// ひとつ前のキー入力を保持
		oldKeyPressFrame[i] = nowKeyPressFrame[i];
		// 現在、キーが押されているとき
		if (keyState[i] != 0)
		{
			// 押されているフレーム数をカウントアップ
			nowKeyPressFrame[i]++;
		}
		else if(keyState[i] == 0)
		{
			// 押されていないなら、フレーム数をゼロクリア
			nowKeyPressFrame[i] = 0;
		}
	}
}

// 引数：DXライブラリのキーコード（KEY_INPUT_で始まるマクロ定義）
bool KeyDown(int KEY_INPUT_)
{
	// 現在押されているキーのフレーム数が０よりも上なら
	if (nowKeyPressFrame[KEY_INPUT_] > 0)
	{
		return true;		//押した
	}

	return false;		// 押していない
}

// 引数：DXライブラリのキーコード（KEY_INPUT_で始まるマクロ定義）
// 説明：「キーを押す→キーを上げる」がセットで行われた時が、クリック
bool KeyClick(int KEY_INPUT_)
{
	// 現在、キーは押されておらず　かつ
	// ひとつ前のキーは押されていたとき
	if (nowKeyPressFrame[KEY_INPUT_] == 0
		&& oldKeyPressFrame[KEY_INPUT_] > 0)
	{
		return true;		//押した
	}

	return false;		// 押していない
}

// 引数：DXライブラリのキーコード（KEY_INPUT_で始まるマクロ定義）
// 注意：戻り値はミリ秒などではなく、フレーム数！
int KeyPressFrame(int KEY_INPUT_)
{
	return nowKeyPressFrame[KEY_INPUT_];
}
