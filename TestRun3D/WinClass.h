#pragma once
#include "Resource.h"

class WinClass : boost::noncopyable
{
	WinClass() = delete;
public:
	static HINSTANCE hInstance;
	static HWND hWnd;
	static std::shared_ptr<class IKeyboard> keyboard;

	explicit WinClass(HINSTANCE newInstance)
	{
		hInstance = newInstance;
		LoadStringW(hInstance, IDS_APP_TITLE, szTitle_, ARRAYSIZE(szTitle_));
		LoadStringW(hInstance, IDC_TESTRUN3D, szWindowClass_, ARRAYSIZE(szTitle_));
		MyRegisterClass();
	}
	int Main(int) const;
private:
	ATOM MyRegisterClass() const;
	BOOL InitInstance(int nCmdShow) const
	{
		hWnd = CreateWindowW(szWindowClass_, szTitle_, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
		if (!hWnd) return FALSE;

		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);

		return TRUE;
	}

	static const size_t MAX_LOADSTRING = 100;
	TCHAR szTitle_[MAX_LOADSTRING];
	TCHAR szWindowClass_[MAX_LOADSTRING];
};