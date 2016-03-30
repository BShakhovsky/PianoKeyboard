#include "stdafx.h"
#include "Keyboard3D.h"

Keyboard3D::Keyboard3D(const HWND hWnd, LPCTSTR path)
	: IKeyboard(hWnd, path)
{
}
Keyboard3D::~Keyboard3D()
{
}

void Keyboard3D::UpdateSize(const HWND hWnd, const UINT width, const UINT height) const
{
}

void Keyboard3D::AddKey(const int16_t note) const
{
}
void Keyboard3D::ReleaseWhiteKeys() const
{
}

void Keyboard3D::AssignFinger(const int16_t note, const char* fingers, const bool leftHand) const
{
}

void Keyboard3D::Draw(const HDC hdc) const
{
}