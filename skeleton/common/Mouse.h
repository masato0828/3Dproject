#pragma once
#include <DxLib.h>

// マクロ定義
#define MouseKindMax			8        // マウスのボタンの種類
#define MouseCodeErrIndex		999		 // マウスコードを変換した要素数のエラー数

//構造体
typedef struct _MousePoint
{
	int x;		// マウスのX位置
	int y;		// マウスのY位置
}MousePoint;

// 外部のプロトタイプ宣言
extern void MouseNowIntoOld(void);							// Now???系の変数の値をOld???系の変数へ入れる
extern int MouseCodeToIndex(int MOUSE_INPUUT_);				// マウスのボタンコードを配列の要素数に変換する
												
extern void MouseInit(void);								// マウス処理の初期化
extern void MouseUpdate(int gameWidht, int gameheight);	// マウス処理の更新
extern bool MouseDown(int MOUSE_INPUT_);					// 特定のボタンを押したか？
extern bool MouseClick(int MOUSE_INPUT_);					// 特定のボタンをクリックしたか？
extern int MousePressFrame(int MOUSE_INPUT_);				// 特定のボタンを押したフレーム数
												
extern MousePoint GetPointMouse(void);						// マウスの現在位置を取得する
extern MousePoint GetOldPointMouse(void);					// マウスの以前の位置を取得する
extern MousePoint GetDiffPointMouse(void);					// マウスの依然と現在の位置の差を取得する
												
extern int GetWheelMouse(void);								// マウスの現在ホイール値を取得する

extern bool CollRectToMousePoint(RECT rect);	// 矩形とマウスの点が当たっているか？
extern bool CollWindowToMousePoint(int gameWidth, int gameHeight);	// 画面とマウスの点が当たっているか？

extern bool CollRectToMouseDown(RECT rect, int MOUSE_INPUT_);	//矩形内でマウスのボタンを押したか？
extern bool CollRectToMouseClick(RECT rect, int MOUSE_INPUT_);	//矩形内でマウスのボタンをクリックしたか？

extern bool CollWindowToMouseDown(int gameWidth, int gameHeight, int MOUSE_INPUT_);	//画面のどこかででマウスのボタンを押したか？
extern bool CollWindowToMouseClick(int gameWidth, int gameHeight, int MOUSE_INPUT_);	//画面のどこかでマウスのボタンをクリックしたか？
