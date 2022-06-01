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
	SetGraphMode(1200, 720, 32);

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
		

		int LEN_LINE = 5000.0f;
		for (int x = 0; x < 1111; x++)
		{
			DrawLine3D(
				VGet(-LEN_LINE, 0.0f, -LEN_LINE + x * 100),
				VGet(LEN_LINE, 0.0f, LEN_LINE + x*100),
				0xffffff);

			DrawLine3D(
				VGet(-LEN_LINE + x * 100, 0.0f, LEN_LINE),
				VGet(-LEN_LINE + x * 100, 0.0f, -LEN_LINE),
				0x00ff00);
		}

		DrawLine3D(
			VGet(0.0f, LEN_LINE, 0.0f),
			VGet(0.0f, -LEN_LINE, 0.0f),
			0x0000ff);

		ScreenFlip();// ��ʓ���ւ�

		
	}

	// �\�t�g�̏I��
	DxLib_End();
}