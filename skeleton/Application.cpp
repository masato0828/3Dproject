#include <DxLib.h>
#include "Application.h"

Application::Application()
{
}

Application::~Application()
{
}

bool Application::Init(void)
{
	// ��ʂ̑傫��
	SetGraphMode(1200, 800, 32);

	/// �E�B���h�E���[�h�A�t���X�N���[�����[�h�̕ύX���s��
	/// <true>�E�B���h�E���[�h
	/// <false>�t���X�N���[��
	ChangeWindowMode(true);

	// Dxlib�̏�����
	if (DxLib_Init() == -1)
	{
		// error���N������I��
		return false;
	}

	// �J���������l�������̂��ߏ����l��^�񒆂ɂ���
	SetCameraPositionAndTargetAndUpVec(VGet(0, 200, -400)/*���_*/, VGet(0, 0, 0)/*���Ă�ꏊ*/, VGet(0, 1, 0)/*�B��ł��Ȃ��Ƃ��邭����*/);


	posX = 0.0f;
	posY = 0.0f;

	return true;
}

void Application::Run(void)
{
	// ESC�L�[�������ƃv���O�����I��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{


		ClsDrawScreen();// ��ʂ̏�Ԃ̏�����

		//DrawLine(0, 0, 100, 0, 0xffffff,true);
		//DrawBox(0,0,100,100,0xffffff,true);
		if (CheckHitKey(KEY_INPUT_UP))
		{
			posX -= blockSize;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			posX += blockSize;
		}

		int LEN_LINE = 500.0f;
		
		

		for (int x = 0; x < 21; x++)
		{
			// ����
			DrawLine3D(
				VGet(-LEN_LINE, 0.0f,-LEN_LINE + x * blockSize),
				VGet(LEN_LINE, 0.0f, -LEN_LINE + x* blockSize),
				0xffffff);

			// �c��
			DrawLine3D(
				VGet( -LEN_LINE + x * blockSize, 0.0f, +LEN_LINE),
				VGet(-LEN_LINE + x * blockSize, 0.0f,  -LEN_LINE),
				0x00ff00);
		}

		// ������
		DrawLine3D(
			VGet(0.0f, LEN_LINE, 0.0f),
			VGet(0.0f, 0.0f, 0.0f),
			0x0000ff);


		ScreenFlip();// ��ʓ���ւ�

		
	}

	// �\�t�g�̏I��
	DxLib_End();
}