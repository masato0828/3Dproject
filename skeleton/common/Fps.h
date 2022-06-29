#pragma once

#include <DxLib.h>

// マクロ定義
#define GameFPS					60	// 設定したいフレームレート

#define MicroSecond		1000000.0f	//1マイクロ秒
#define MillSecond		  1000.0f	//1ミリ秒
#define WaitTimeMill        3000    //最大で待てるミリ数

// 構造体の定義＆名前の再定義
typedef struct _FPS
{
	LONGLONG firstTakeTime = 0;		// 1フレーム目の計測時間
	LONGLONG nowTakeTime = 0;		// 現在の計測時間
	LONGLONG oldTakeTime = 0;		// 以前の計測時間

	float deltatime = 0.000001f;	// デルタタイム(経過時間)
	int frameCount = 1;				// 現在のフレーム数(1フレーム目～MAXフレーム目まで)
	float average = 0.0f;			// 平均FPS値
}FPS;

//外部グローバル変数
extern FPS fps;

extern void FPSInit(void);		//FPS初期化
extern void FPSCheck(void);		//FPS計測
extern void FPSDraw(void);		//FPS描画
extern void FPSWait(void);		//FPS待機
extern float GetDeltaTimes(void);//デルタタイムを取得
