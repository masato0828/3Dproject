#include <DxLib.h>
#include "Application.h"

/// <summary>
/// �G���g���|�C���g
/// </summary>
/// <param name="hInstance">�C���X�^���X�n���h��</param>
/// <param name="hPrevInstance">Win16�̎Y���i���Null�j</param>
/// <param name="lpCmdLine">Windows�W���̕����^</param>
/// <param name="nCmdShow">�A�v���P�[�V�����̏����\�����@�̎w��</param>
/// <returns></returns>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Application app;

	if (!app.Init())
	{
		return -1;
	}

	
	app.Run();
	
	return 0;

}