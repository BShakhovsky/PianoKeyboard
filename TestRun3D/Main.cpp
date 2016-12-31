#include "stdafx.h"
#include "WinClass.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int nCmdShow)
{
	return WinClass(hInstance).Main(nCmdShow);
}