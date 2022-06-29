#include"Fps.h"


//	グローバル変数
FPS fps;

void FPSInit(void)
{
	// Windowsが起動してから現在までの時間を得る（マイクロ秒）
	fps.firstTakeTime = GetNowHiPerformanceCount();

	// 他の値も初期化
	fps.nowTakeTime = fps.firstTakeTime;
	fps.oldTakeTime = fps.firstTakeTime;
	fps.deltatime = 0.000001f;
	fps.frameCount = 1;
	fps.average = 0.0f;

	return;
}

// 計測
void FPSCheck(void)
{
	// 現在の時刻を取得
	fps.nowTakeTime = GetNowHiPerformanceCount();

	// デルタタイムを計算
	fps.deltatime = (fps.nowTakeTime - fps.oldTakeTime) / MicroSecond;

	// 現在の時刻を保存
	fps.oldTakeTime = fps.nowTakeTime;

	// 現在がMAXフレーム目なら
	if (fps.frameCount == GameFPS)
	{
		// 1フレーム目～MAXフレーム目までの合計時間を計算
		float totalFrameTime = fps.nowTakeTime - fps.firstTakeTime;

		// 合計時間を理想のFPS値で割って平均値を計算
		float calcAverage = totalFrameTime / GameFPS;

		// 1秒あたりのフレーム数に変換
 		fps.average = MicroSecond / calcAverage;

		// 1フレーム目の時刻を取得
		fps.firstTakeTime = GetNowHiPerformanceCount();

		// フレーム数を1に戻す
		fps.frameCount = 1;
	}
	else
	{
		// フレーム数をカウントアップ
		fps.frameCount++;
	}

	return;
}

void FPSDraw(void)
{
	DrawFormatString(0,0,0xffffff,"FPS:%3.1f",fps.average);
	
	return;
}

void FPSWait(void)
{
	// 早すぎたときに待機するミリ秒
	int wait = 0;

	// 待ち時間を計測
	wait = 
		MicroSecond / GameFPS * fps.frameCount // 理想の時間
		- (fps.nowTakeTime - fps.firstTakeTime);// 実際の時間

	// マイクロ秒をミリ秒に変換
	wait /= MillSecond;

	// 待ち時間があるならば
	if (wait > 0 && wait <= WaitTimeMill)
	{
		// メッセージを処理しながら待つ
		WaitTimer(wait);
	}

	return;

}

float GetDeltaTimes(void)
{
	return fps.deltatime;
}
