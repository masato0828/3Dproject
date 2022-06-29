#pragma once

//ヘッダファイル読み込み
#include <DxLib.h>

//マクロ定義
#define KeyKindMax 256 // キーの種類

//外部のプロトタイプ宣言
extern void KeyInit(void);						//キーボード処理の初期化
extern void KeyUpdate(void);					//キーボード処理の更新
extern bool KeyDown(int KEY_INPUT_);			//特定のキーを押したか？
extern bool KeyClick(int KEY_INPUT_);			//特定のキーをクリックしたか？
extern int KeyPressFrame(int KEY_INPUT_);		//特定のキーを押したフレーム数