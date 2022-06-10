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

	// �i�[�����f�[�^�̐擪���i�[
	auto itr = filedate.begin();

	// ���邮��	
	for (int i = 0; i < filedate.size(); i++)
	{
		// �t�@�C�����[�h
 		keymap.emplace(itr->first, MV1LoadModel(("model/map/Plane(mv1)/" + itr->first +".mv1").c_str()));
		//modeldata.push_back(MV1LoadModel(("model/map/Plane(mv1)/" + itr->first + ".mv1").c_str()));
		// �d�������t�@�C�������΂�����
		auto count = filedate.count(itr->first);
		std::advance(itr , count);

		i += count-1;
	}





	int file = FileRead_open("mapData/PositionDate.txt");

	int LineCounter;
	char StringBuffer[2048];

	// �ǂݍ��݂Ȃ���s���𐔂���
	LineCounter = 0;
	while (FileRead_eof(file) == 0)	// �t�@�C���̏I�[�ɓ��B����܂Ń��[�v
	{
		// 1�s�ǂݍ���
		FileRead_gets(StringBuffer, sizeof(StringBuffer), file);

		// �s����1���₷
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
	//	// ����
	//	DrawLine3D(
	//		VGet(-LEN_LINE, 0.0f, -LEN_LINE + x * blockSize),
	//		VGet(LEN_LINE, 0.0f, -LEN_LINE + x * blockSize),
	//		0xffffff);

	//	// �c��
	//	DrawLine3D(
	//		VGet(-LEN_LINE + x * blockSize, 0.0f, +LEN_LINE),
	//		VGet(-LEN_LINE + x * blockSize, 0.0f, -LEN_LINE),
	//		0x00ff00);
	//}

	//// ������
	//DrawLine3D(
	//	VGet(0.0f, LEN_LINE, 0.0f),
	//	VGet(0.0f, 0.0f, 0.0f),
	//	0x0000ff);


	// �s����`�悷��
	DrawFormatString(0, 16, GetColor(255, 255, 255), "�s�� : %d", linecount);

	// �t�@�C���ǂݍ��ݕ\��
	// �����s�ڂ̂�
	//DrawFormatString(0, 32, GetColor(255, 255, 255), "%s",filedate.cbegin());

}

bool Stage::MapLoder(std::string fileName)
{
	// ���g���Ȃ��Ƃ�
	if (fileName == "")
	{
		return false;
	}

	// �t�@�C������͗p�̃X�g���[���ɂ��Ĉ������߂̌^
	std::ifstream reading_file;

	// �t�@�C�����I�[�v��
	// �������͏ȗ���(�f�t�H��in�����邪����̓e�X�g�̂��ߋL���Ain�͓ǂݍ��ݐ�p)
	reading_file.open(fileName, std::ios::in);

	// �ǂݍ��񂾃t�@�C����s�̈ꎞ�i�[�p
	std::string reading_line_buffer;

	// �����񂩐��l���𔻕�(true : ������Afalse : ���l)
	auto isNumber = [](const std::string& str)
	{
		for (char const& c : str) {
			if (std::isdigit(c) == 0) return false;
		}
		return true;
	};

	auto isOneNumber = [](const std::string& str)
	{	
		
			// �������ǂ���
		if (std::isdigit(str.at(0)))
		{
			return true;
		}
		else if(!std::isdigit(str.at(0)))
		{
			// �������ǂ���
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
	

	//int�^�ɂ��ĕԂ�
	auto getInt = [](std::istringstream& stremBuf, std::string& buf)
	{
		std::getline(stremBuf, buf,',');
		return atoi(buf.c_str());
	};

	// double�^�ɂ��ĕԂ�
	auto getDouble = [](std::istringstream& stremBuf, std::string& buf)
	{
		std::getline(stremBuf, buf, ',');
		return atof(buf.c_str());
	};

	std::string objName;
	std::vector<VECTOR> pos;
	std::vector<VECTOR> rotate;
	// �t�@�C���̖����܂œǂݍ���
	while (std::getline(reading_file, reading_line_buffer))
	{
		// �R���|�[�l���g���̎擾
		// filedate�Ɋi�[
		if (!isOneNumber(reading_line_buffer))
		{
			objName = reading_line_buffer;
		}


		// �ʒu�̎擾
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


		// ��]�̎擾
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


			// ���ꂼ��ɓ����Ă���f�[�^�̖������Q��
			VECTOR finelPos = VGet(pos.back().x, pos.back().y, pos.back().z);
			VECTOR finelRotate = VGet(rotate.back().x, rotate.back().y, rotate.back().z);

			// �Ō�ɗv�f�������i�I�u�W�F�N�g���A�ʒu�j
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
