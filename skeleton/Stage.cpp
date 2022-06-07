#include <Dxlib.h>
#include <fstream>
#include <iostream>
#include <vector>
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

		// 行数を1増やす
		LineCounter++;
	}

	linecount = LineCounter;

	FileRead_close(file);

	MapLoder("mapData/PositionDate.txt");
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

	// ファイル読み込み表示
	// 現状一行目のみ
	//DrawFormatString(0, 32, GetColor(255, 255, 255), "%s",filedate.cbegin());

}

bool Stage::MapLoder(std::string fileName)
{
	// 中身がないとき
	if (fileName == "")
	{
		return false;
	}

	// ファイルを入力用のストリームにして扱うための型
	std::ifstream reading_file;

	// ファイルをオープン
	// 第二引数は省略可(デフォでinが入るが今回はテストのため記入、inは読み込み専用)
	reading_file.open(fileName, std::ios::in);

	// 読み込んだファイル一行の一時格納用
	std::string reading_line_buffer;

	// 文字列か数値かを判別(true : 文字列、false : 数値)
	auto isNumber = [](const std::string& str)
	{
		for (char const& c : str) {
			if (std::isdigit(c) == 0) return false;
		}
		return true;
	};

	auto isOneNumber = [](const std::string& str)
	{	
		//// 負数かどうか
		//float s = str.at(0) + str.at(1);
		//if (!std::signbit(s))
		//{
			// 文字かどうか
			if (std::isdigit(str.at(0)) == 0)
			{

				return false;
			}
		//}
		return true;
	};
	

	//int型にして返す
	auto getInt = [](std::ifstream& stremBuf, std::string& buf) 
	{
		std::getline(stremBuf, buf,',');
		return atoi(buf.c_str());
	};

	// double型にして返す
	auto getDouble = [](std::ifstream& stremBuf, std::string& buf)
	{
		std::getline(stremBuf, buf, ',');
		return atof(buf.c_str());
	};

	std::string objName;
	std::vector<VECTOR> pos;
	std::vector<VECTOR> rotate;
	//pos.emplace_back(VGet(0, 0, 0));
	//rotate.emplace_back(VGet(0, 0, 0));
	// ファイルの末尾まで読み込む
	while (std::getline(reading_file, reading_line_buffer))
	{
		// コンポーネント名の取得
		// filedateに格納
		if (!isOneNumber(reading_line_buffer))
		{
			objName = reading_line_buffer;
		}

		//// 位置の取得
		//while (std::getline(reading_file, reading_line_buffer))
		//{
		//	if (!isNumber(reading_line_buffer))
		//	{
		//		pos.emplace_back(VGet(5, 10, 15));
		//	}
		//	// 回転の取得
		//	while (std::getline(reading_file, reading_line_buffer))
		//	{
		//		if (!isNumber(reading_line_buffer))
		//		{
		//			rotate.emplace_back(VGet(50.0, 100.0, 150.0));
		//		}

		//		VECTOR finelPos = VGet(pos.data()->x, pos.data()->y, pos.data()->z);
		//		VECTOR finelRotate = VGet(rotate.data()->x, rotate.data()->y, rotate.data()->z);

		//		// 最後に要素をいれる（オブジェクト名、位置）
		//		filedate.insert(std::make_pair(objName,std::make_pair(finelPos,finelRotate)));
		//	}

		//	break;
		//}
	}

	reading_file.close();

	return true;
}
