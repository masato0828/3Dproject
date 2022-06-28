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
	//player = std::make_unique<Player>(this);
	stage = std::make_unique<Stage>();
	camera = std::make_unique<Camera>();
	camera->SetPlayer(player);

	return true;
}

void Application::Run(void)
{
	// ESC�L�[�������ƃv���O�����I��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//player->Update();
		stage->Update();
		camera->Updata();
		

		ClsDrawScreen();// ��ʂ̏�Ԃ̏�����
		
		stage->Draw();
		//player->Draw();
		camera->Draw();
		
		

		ScreenFlip();// ��ʓ���ւ�

		
	}

	// �\�t�g�̏I��
	DxLib_End();
}

Camera* Application::GetCamera()
{
	return camera.get();
}
