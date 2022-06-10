#include <Dxlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Utility.h"
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
	testmHndle = MV1LoadModel("model/test.mv1");

	angle_ = {0,0,0};



	MapLoder("mapData/PositionDate.txt");

	// 格納したデータの先頭を格納
	auto itr = filedate.begin();

	// ぐるぐる	
	for (int i = 0; i < filedate.size(); i++)
	{
		// ファイルロード
 		keymap.emplace(itr->first, MV1LoadModel(("model/map/Plane(mv1)/" + itr->first +".mv1").c_str()));
		//modeldata.push_back(MV1LoadModel(("model/map/Plane(mv1)/" + itr->first + ".mv1").c_str()));
		// 重複したファイル名を飛ばす処理
		auto count = filedate.count(itr->first);
		std::advance(itr , count);

		i += count-1;
	}





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

	angle = 0;
	FileRead_close(file);
}

void Stage::Update()
{
	if (CheckHitKey(KEY_INPUT_UP))
	{
		angle_.x -= 0.01;
	}
	
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		angle_.y -= 0.01;
	}
	
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		angle_.z -= 0.01;
	}
	
	



}

void Stage::Draw()
{
	int LEN_LINE = 500.0f;
	auto blockSize = 50.0f;


	//for (const auto& key : modeldata)
	//{
		for (const auto& [key_,data] : filedate)
		{


				MV1SetPosition(keymap.at(key_), VGet(data.first.x, data.first.y, data.first.z));

				//DrawSphere3D(VGet(data.first.x, 30, data.first.z),10,10,0x00ff00,0xffffff,true);
				


				MV1SetRotationXYZ(keymap.at(key_), DegRadVGet(0, data.second.y, 0));
				//MV1SetRotationXYZ(keymap.at(key_), DegRadVGet(0, data.second.y,0 ));

				MV1DrawModel(keymap.at(key_));

				DrawLine3D(VGet(data.first.x, data.first.y, data.first.z), VGet(data.first.x, data.first.y + 200, data.first.z), 0x00ff00);
		}


		MV1DrawModel(testmHndle);

		MV1SetPosition(testmHndle,VGet(0,100,0));
		MV1SetRotationXYZ(testmHndle, angle_);
		

		
				DrawString(1100, 200 + (16 * 1), "x", 0xffffff);
				DrawFormatString(1100+16, 200 + (16 * 1), 0xffffff,"%f",Utility::Rad2DegF( angle_.x));
		
				DrawString(1100, 200 + (16 * 2), "y", 0xffffff);
				DrawFormatString(1100+16, 200 + (16 * 2), 0xffffff, "%f", Utility::Rad2DegF(angle_.y));
	
				DrawString(1100, 200 + (16 * 3), "z", 0xffffff);
				DrawFormatString(1100+16, 200 + (16 * 3), 0xffffff, "%f", Utility::Rad2DegF(angle_.z));
		

	//	
	//}

	//for (int x = 0; x < 21; x++)
	//{
	//	// 横線
	//	DrawLine3D(
	//		VGet(-LEN_LINE, 0.0f, -LEN_LINE + x * blockSize),
	//		VGet(LEN_LINE, 0.0f, -LEN_LINE + x * blockSize),
	//		0xffffff);

	//	// 縦線
	//	DrawLine3D(
	//		VGet(-LEN_LINE + x * blockSize, 0.0f, +LEN_LINE),
	//		VGet(-LEN_LINE + x * blockSize, 0.0f, -LEN_LINE),
	//		0x00ff00);
	//}

	//// 中央線
	//DrawLine3D(
	//	VGet(0.0f, LEN_LINE, 0.0f),
	//	VGet(0.0f, 0.0f, 0.0f),
	//	0x0000ff);


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
		
			// 文字かどうか
		if (std::isdigit(str.at(0)))
		{
			return true;
		}
		else if(!std::isdigit(str.at(0)))
		{
			// 負数かどうか
			double number = atoi(str.c_str());
			number = number * number;
			if (number < 0)
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	};
	

	//int型にして返す
	auto getInt = [](std::istringstream& stremBuf, std::string& buf)
	{
		std::getline(stremBuf, buf,',');
		return atoi(buf.c_str());
	};

	// double型にして返す
	auto getDouble = [](std::istringstream& stremBuf, std::string& buf)
	{
		std::getline(stremBuf, buf, ',');
		return atof(buf.c_str());
	};

	std::string objName;
	std::vector<VECTOR> pos;
	std::vector<VECTOR> rotate;
	// ファイルの末尾まで読み込む
	while (std::getline(reading_file, reading_line_buffer))
	{
		// コンポーネント名の取得
		// filedateに格納
		if (!isOneNumber(reading_line_buffer))
		{
			objName = reading_line_buffer;
		}


		// 位置の取得
		while (std::getline(reading_file, reading_line_buffer))
		{
			if (isOneNumber(reading_line_buffer))
			{
				std::istringstream file_line(reading_line_buffer);
				std::string str_buf;
				int x = getInt(file_line, str_buf);
				int y = getInt(file_line, str_buf);
				int z = getInt(file_line, str_buf);
				pos.emplace_back(VGet(x, y, z));
			}
			break;
		}


		// 回転の取得
		while (std::getline(reading_file, reading_line_buffer))
		{
			if (isOneNumber(reading_line_buffer))
			{
				std::istringstream file_line(reading_line_buffer);
				std::string str_buf;

				int x = getInt(file_line, str_buf);
				int y = getInt(file_line, str_buf);
				int z = getInt(file_line, str_buf);
				rotate.emplace_back(VGet(
					x,y,z
				));
			}


			// それぞれに入っているデータの末尾を参照
			VECTOR finelPos = VGet(pos.back().x, pos.back().y, pos.back().z);
			VECTOR finelRotate = VGet(rotate.back().x, rotate.back().y, rotate.back().z);

			// 最後に要素をいれる（オブジェクト名、位置）
			filedate.insert(std::make_pair(objName, std::make_pair(finelPos, finelRotate)));
			break;
		}
		
		
	}


	reading_file.close();

	return true;
}

VECTOR Stage::DegRadVGet(double x, double y, double z)
{
	return VGet(Utility::Deg2RadD(x), Utility::Deg2RadD(y), Utility::Deg2RadD(z));
}
