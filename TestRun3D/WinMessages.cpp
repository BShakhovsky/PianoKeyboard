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

#pragma warning(push)
#pragma warning(disable:4711)	// automatic inline expansion
void CALLBACK OnTimer(const HWND, UINT, UINT_PTR, const DWORD dwTime)
{
	static const auto start(dwTime);
	const auto note(static_cast<int16_t>((dwTime - start) / 200 % 88 + 21));

	auto volume(static_cast<float>(note % 24) / 12);
	if (volume > 1) volume = 2 - volume;

	WinClass::keyboard->ReleaseKeys();
	WinClass::keyboard->NormalizeVolume(note / 24 % 2 == 0);
	WinClass::keyboard->PressKey(make_pair(note, volume));
	WinClass::keyboard->AssignFinger(note,
		string(static_cast<size_t>(note % 3), static_cast<char>('0' + note % 6)).c_str(),
		dwTime /200 % 10 == 0);
	WinClass::keyboard->Update();
}

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT)
{
	TCHAR path[MAX_PATH];
	GetCurrentDirectory(ARRAYSIZE(path), path);
	WinClass::keyboard = make_shared<Keyboard3D>(hWnd, path);

	// Potentially throwing function passed to extern C function
	// Undefined behavior may occur if this function throws
#pragma warning(suppress:5039)
	SetTimer(hWnd, 0, 200, OnTimer);

	return true;
}

void WinMessages::OnSize(const HWND, const UINT, const int cx, const int cy)
{
	width = static_cast<UINT>(cx);
	height = static_cast<UINT>(cy);

	WinClass::keyboard->UpdateSize(width, height);
	WinClass::keyboard->Update();
}
inline void OnMove(HWND, int, int)
{
	WinClass::keyboard->Update();
}
#pragma warning(pop)

inline void OnCommand(HWND hWnd, int id, HWND, UINT)
{
	switch (id)
	{
		// Potentially throwing function passed to extern C function
		// Undefined behavior may occur if this function throws
#pragma warning(suppress:5039)
	case IDM_ABOUT:	DialogBox(WinClass::hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About); break;
	case IDM_EXIT:	DestroyWindow(hWnd);
	}
}
inline void OnDestroy(HWND)
{
	PostQuitMessage(0);
}

void OnMouseWheel(HWND, int, int, int delta, UINT)
{
	WinClass::keyboard->Zoom3D(delta / WHEEL_DELTA);
}
void OnMButtonDblClick(HWND, BOOL, int, int, UINT)
{
	WinClass::keyboard->Fit3DToWindow();
}

void OnMButtonDown(HWND, BOOL, int x, int y, UINT)
{
	WinClass::keyboard->Move3DStart(x, y);
}
void OnLButtonDown(HWND, BOOL, int x, int y, UINT)
{
	WinClass::keyboard->Rotate3DStart(x, y);
}
void OnMouseMove(HWND, int x, int y, UINT keyFlags)
{
	WinClass::keyboard->On3DMouseMove(x, y, (keyFlags & MK_MBUTTON) != 0, (keyFlags & MK_LBUTTON) != 0);
}

void OnContextMenu(HWND hWnd, HWND, int xPos, int yPos)
{
	if (TrackPopupMenu(GetSubMenu(LoadMenu(WinClass::hInstance,
		MAKEINTRESOURCE(IDR_CONTEXT_MENU)), 0), TPM_CENTERALIGN | TPM_VCENTERALIGN | TPM_RETURNCMD,
		xPos, yPos, 0, hWnd, nullptr) == IDM_DEFAULT_POS) WinClass::keyboard->Restore3DPosition();
}

LRESULT CALLBACK WinMessages::Main(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);

		HANDLE_MSG(hWnd, WM_SIZE, OnSize);
		HANDLE_MSG(hWnd, WM_MOVE, OnMove);

		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);

		HANDLE_MSG(hWnd, WM_MOUSEWHEEL, OnMouseWheel);
		HANDLE_MSG(hWnd, WM_MBUTTONDBLCLK, OnMButtonDblClick);

		HANDLE_MSG(hWnd, WM_MBUTTONDOWN, OnMButtonDown);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);

		HANDLE_MSG(hWnd, WM_CONTEXTMENU, OnContextMenu);

	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
}