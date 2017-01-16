#include "stdafx.h"
#include "Keyboard3D.h"
#include "Render.h"
#include "DxError.h"

Keyboard3D::Keyboard3D(const HWND hWnd,
	const float cameraX, const float cameraY, const float cameraZ,
	LPCTSTR path, const bool isVolumeNormalized)

	: IKeyboard(hWnd, path, isVolumeNormalized),
	render_(nullptr),
	cameraX_(cameraX), cameraY_(cameraY), cameraZ_(cameraZ),
	path_(path)
{}

Keyboard3D::~Keyboard3D()
{
	delete render_;
}

#define RENDER(DO_WHAT) if (render_) try { render_-> ## DO_WHAT ; } catch (const DxError& e) \
	{ MessageBox(GetActiveWindow(), e.RusWhat(), TEXT("DirectX Error"), MB_OK | MB_ICONHAND); }

void Keyboard3D::UpdateSize(const HWND hWnd, const UINT width, const UINT height)
{
	RENDER(Resize(width, height))
else try
	{
		render_ = new Render(hWnd, width, height, cameraX_, cameraY_, cameraZ_, path_.c_str());
	}
	catch (const DxError& e)
	{
		MessageBox(hWnd, e.RusWhat(), TEXT("DirectX Error"), MB_OK | MB_ICONHAND);
	}
}

void Keyboard3D::ReleaseKeys() const
{
	RENDER(ReleaseAllKeys());
}

void Keyboard3D::AddKey(const int16_t note) const
{
	assert("Note is outside the keyboard" && note >= minNote && note <= maxNote);
	RENDER(PressKey(note - 21));
}

void Keyboard3D::AssignFinger(const int16_t note, const char* fingers, const bool leftHand) const
{
	assert("Note is outside the keyboard" && note >= minNote && note <= maxNote);
	RENDER(AssignFingerNums(note - 21, fingers, leftHand));
}

void Keyboard3D::Draw(const HDC) const
{
	RENDER(Draw());
}