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
	if (render_) delete render_;
}


void Keyboard3D::UpdateSize(const HWND hWnd, const UINT width, const UINT height)
{
	if (render_) delete render_;
	try
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
	if (render_) try
	{
		render_->ReleaseAllKeys();
	}
	catch (const DxError& e)
	{
		MessageBoxA(GetActiveWindow(), e.what(), "DirectX Error", MB_OK | MB_ICONHAND);
	}
}

void Keyboard3D::AddKey(const int16_t note) const
{
	assert("Note must be in the range [21...108]" && note >= 21 && note <= 108);

	if (render_) try
	{
		render_->PressKey(note - 21);
	}
	catch (const DxError& e)
	{
		MessageBoxA(GetActiveWindow(), e.what(), "DirectX Error", MB_OK | MB_ICONHAND);
	}
}

void Keyboard3D::AssignFinger(const int16_t note, const char* fingers, const bool leftHand) const
{
	assert("Note must be in the range [21...108]" && note >= 21 && note <= 108);

	if (render_) try
	{
		render_->AssignFingerNums(note - 21, fingers, leftHand);
	}
	catch (const DxError& e)
	{
		MessageBoxA(GetActiveWindow(), e.what(), "DirectX Error", MB_OK | MB_ICONHAND);
	}
}

void Keyboard3D::Draw(const HDC) const
{
	if (render_) try
	{
		render_->Draw();
	}
	catch (const DxError& e)
	{
		MessageBoxA(GetActiveWindow(), e.what(), "DirectX Error", MB_OK | MB_ICONHAND);
	}
}