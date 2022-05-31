#include <DxLib.h>
#include "Application.h"

/// <summary>
/// エントリポイント
/// </summary>
/// <param name="hInstance">インスタンスハンドル</param>
/// <param name="hPrevInstance">Win16の産物（常にNull）</param>
/// <param name="lpCmdLine">Windows標準の文字型</param>
/// <param name="nCmdShow">アプリケーションの初期表示方法の指定</param>
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