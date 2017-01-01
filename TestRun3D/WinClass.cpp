#include "stdafx.h"
#include "WinClass.h"
#include "WinMessages.h"
#include "Keyboard3D.h"
#include "vld.h"

using namespace std;

HINSTANCE WinClass::hInstance = nullptr;
HWND WinClass::hWnd = nullptr;
shared_ptr<IKeyboard> WinClass::keyboard = nullptr;

ATOM WinClass::MyRegisterClass() const
{
	WNDCLASSEXW wcex{ sizeof wcex };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WinMessages::Main;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTRUN3D));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TESTRUN3D);
	wcex.lpszClassName = szWindowClass_;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassExW(&wcex);
}

int WinClass::Main(const int nCmdShow) const
{
	if (!InitInstance(nCmdShow)) return FALSE;

	const auto hAccelTable(LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTRUN3D)));
	MSG msg{ 0 };

#ifdef _DEBUG
	const auto before(VLDGetLeaksCount());
#endif

	while (msg.message != WM_QUIT)
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) && !TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else keyboard->Update();

#ifdef _DEBUG
		const auto after(VLDGetLeaksCount());
#endif
//	assert("Memory leaks detected" && before == after);

	return static_cast<int>(msg.wParam);
}