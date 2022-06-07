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
		// ����
		DrawLine3D(
			VGet(-LEN_LINE, 0.0f, -LEN_LINE + x * blockSize),
			VGet(LEN_LINE, 0.0f, -LEN_LINE + x * blockSize),
			0xffffff);

		// �c��
		DrawLine3D(
			VGet(-LEN_LINE + x * blockSize, 0.0f, +LEN_LINE),
			VGet(-LEN_LINE + x * blockSize, 0.0f, -LEN_LINE),
			0x00ff00);
	}

	// ������
	DrawLine3D(
		VGet(0.0f, LEN_LINE, 0.0f),
		VGet(0.0f, 0.0f, 0.0f),
		0x0000ff);


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
		//// �������ǂ���
		//float s = str.at(0) + str.at(1);
		//if (!std::signbit(s))
		//{
			// �������ǂ���
			if (std::isdigit(str.at(0)) == 0)
			{

				return false;
			}
		//}
		return true;
	};
	

	//int�^�ɂ��ĕԂ�
	auto getInt = [](std::ifstream& stremBuf, std::string& buf) 
	{
		std::getline(stremBuf, buf,',');
		return atoi(buf.c_str());
	};

	// double�^�ɂ��ĕԂ�
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
	// �t�@�C���̖����܂œǂݍ���
	while (std::getline(reading_file, reading_line_buffer))
	{
		// �R���|�[�l���g���̎擾
		// filedate�Ɋi�[
		if (!isOneNumber(reading_line_buffer))
		{
			objName = reading_line_buffer;
		}

		//// �ʒu�̎擾
		//while (std::getline(reading_file, reading_line_buffer))
		//{
		//	if (!isNumber(reading_line_buffer))
		//	{
		//		pos.emplace_back(VGet(5, 10, 15));
		//	}
		//	// ��]�̎擾
		//	while (std::getline(reading_file, reading_line_buffer))
		//	{
		//		if (!isNumber(reading_line_buffer))
		//		{
		//			rotate.emplace_back(VGet(50.0, 100.0, 150.0));
		//		}

		//		VECTOR finelPos = VGet(pos.data()->x, pos.data()->y, pos.data()->z);
		//		VECTOR finelRotate = VGet(rotate.data()->x, rotate.data()->y, rotate.data()->z);

		//		// �Ō�ɗv�f�������i�I�u�W�F�N�g���A�ʒu�j
		//		filedate.insert(std::make_pair(objName,std::make_pair(finelPos,finelRotate)));
		//	}

		//	break;
		//}
	}

	reading_file.close();

	return true;
}
