#include "stdafx.h"
#include "WinMessages.h"
#include "WinClass.h"
#include "Keyboard3D.h"

using namespace std;

UINT WinMessages::width = 0, WinMessages::height = 0;

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM)
{
	switch (message)
	{
	case WM_INITDIALOG:	return TRUE;
	case WM_COMMAND:	if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
	{
		EndDialog(hDlg, LOWORD(wParam));
		return TRUE;
	}
	}
	return FALSE;
}


void CALLBACK OnTimer(const HWND hWnd, UINT, UINT_PTR, const DWORD dwTime)
{
	static const auto start(dwTime);
	const auto note(static_cast<int16_t>((dwTime - start) / 200 % 88 + 21));

	WinClass::keyboard->ReleaseKeys();
	WinClass::keyboard->PressKey(note);
	WinClass::keyboard->AssignFinger(note,
		string(static_cast<size_t>(note % 3), static_cast<char>('0' + note % 6)).c_str(),
		dwTime /200 % 10 == 0);
	WinClass::keyboard->Update();
}

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT)
{
	TCHAR path[MAX_PATH];
	GetCurrentDirectory(ARRAYSIZE(path), path);
	WinClass::keyboard = make_shared<Keyboard3D>(hWnd, 26.0f, 25.0f, 30.0f, path);

	SetTimer(hWnd, 0, 200, OnTimer);

	return true;
}

void WinMessages::OnSize(const HWND hWnd, const UINT, const int cx, const int cy)
{
	width = static_cast<UINT>(cx);
	height = static_cast<UINT>(cy);

	WinClass::keyboard->UpdateSize(hWnd, width, height);
	WinClass::keyboard->Update();
}
void OnMove(HWND hWnd, int, int)
{
	WinClass::keyboard->Update();
}
inline void OnCommand(HWND hWnd, int id, HWND, UINT)
{
	switch (id)
	{
	case IDM_ABOUT:	DialogBox(WinClass::hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About); break;
	case IDM_EXIT:	DestroyWindow(hWnd);
	}
}
inline void OnDestroy(HWND)
{
	PostQuitMessage(0);
}

LRESULT CALLBACK WinMessages::Main(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);
		HANDLE_MSG(hWnd, WM_MOVE, OnMove);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
}