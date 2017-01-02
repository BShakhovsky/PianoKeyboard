#include "stdafx.h"
#include "Keyboard3D.h"
#include "Render.h"
#include "DxError.h"

Keyboard3D::Keyboard3D(const HWND hWnd,
	const float cameraX, const float cameraY, const float cameraZ,
	LPCTSTR path)

	: IKeyboard(hWnd, path),
	render_(nullptr),
	cameraX_(cameraX), cameraY_(cameraY), cameraZ_(cameraZ),
	path_(path)
{}

Keyboard3D::~Keyboard3D()
{
	delete render_;
}

#define RENDER(DO_WHAT) if (render_) try { render_-> ## DO_WHAT ; } catch (const DxError& e) \
	{ MessageBoxA(GetActiveWindow(), e.what(), "DirectX Error", MB_OK | MB_ICONHAND); }

void Keyboard3D::UpdateSize(const HWND hWnd, const UINT width, const UINT height)
{
	RENDER(Resize(width, height))
else try
	{
		render_ = new Render(hWnd, width, height, cameraX_, cameraY_, cameraZ_, path_.c_str());
	}
	catch (const DxError& e)
	{
		MessageBoxA(hWnd, e.what(), "DirectX Error", MB_OK | MB_ICONHAND);
	}
}

void Keyboard3D::ReleaseKeys() const
{
	RENDER(ReleaseAllKeys());
}

void Keyboard3D::AddKey(const int16_t note) const
{
	assert("Note must be in the range [21...108]" && note >= 21 && note <= 108);

	RENDER(PressKey(note - 21));
}

void Keyboard3D::AssignFinger(const int16_t note, const char* fingers, const bool leftHand) const
{
	assert("Note must be in the range [21...108]" && note >= 21 && note <= 108);

	RENDER(AssignFingerNums(note - 21, fingers, leftHand));
}

void Keyboard3D::Draw(const HDC) const
{
	RENDER(Draw());
}