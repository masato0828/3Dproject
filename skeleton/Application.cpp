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


		ScreenFlip();// ��ʓ���ւ�

		
	}

	// �\�t�g�̏I��
	DxLib_End();
}