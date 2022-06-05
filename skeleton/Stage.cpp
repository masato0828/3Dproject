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

	//int LineCounter;
	//char StringBuffer[2048];
	//int FileHandle;

	//// �ǂݍ��݂Ȃ���s���𐔂���
	//LineCounter = 0;
	//while (FileRead_eof(FileHandle) == 0)	// �t�@�C���̏I�[�ɓ��B����܂Ń��[�v
	//{
	//	// 1�s�ǂݍ���
	//	FileRead_gets(StringBuffer, sizeof(StringBuffer), FileHandle);

	//	// �s����1���₷
	//	LineCounter++;
	//}

	//// �s����`�悷��
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "�s�� : %d", LineCounter);


	// ���O���擾
	// �ʒu���擾
	// ��]���擾





	// ���[�v�擾

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

}
