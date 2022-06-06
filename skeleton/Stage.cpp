#include <Dxlib.h>
#include "Stage.h"

Stage::Stage()
{
	Init();
}

Stage::~Stage()
{
}

void Stage::Init()
{
	int file = FileRead_open("mapData/PositionDate.txt");

	int LineCounter;
	char StringBuffer[2048];

	// 読み込みながら行数を数える
	LineCounter = 0;
	while (FileRead_eof(file) == 0)	// ファイルの終端に到達するまでループ
	{
		// 1行読み込む
		FileRead_gets(StringBuffer, sizeof(StringBuffer), file);

		// 名前を取得
		
		// 位置を取得
		// 回転を取得

		// 行数を1増やす
		LineCounter++;
	}

	


	



	linecount = LineCounter;

	// ループ取得

	FileRead_close(file);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	int LEN_LINE = 500.0f;
	auto blockSize = 50.0f;


	for (int x = 0; x < 21; x++)
	{
		// 横線
		DrawLine3D(
			VGet(-LEN_LINE, 0.0f, -LEN_LINE + x * blockSize),
			VGet(LEN_LINE, 0.0f, -LEN_LINE + x * blockSize),
			0xffffff);

		// 縦線
		DrawLine3D(
			VGet(-LEN_LINE + x * blockSize, 0.0f, +LEN_LINE),
			VGet(-LEN_LINE + x * blockSize, 0.0f, -LEN_LINE),
			0x00ff00);
	}

	// 中央線
	DrawLine3D(
		VGet(0.0f, LEN_LINE, 0.0f),
		VGet(0.0f, 0.0f, 0.0f),
		0x0000ff);


	// 行数を描画する
	DrawFormatString(0, 16, GetColor(255, 255, 255), "行数 : %d", linecount);

}
