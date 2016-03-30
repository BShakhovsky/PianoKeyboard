#pragma once
#include "IKeyboard.h"

class Keyboard3D : public IKeyboard
{
	Keyboard3D() = delete;
public:
	explicit Keyboard3D(HWND, LPCTSTR path);
	virtual ~Keyboard3D() override final;

	virtual void UpdateSize(HWND, UINT width, UINT height) const override final;
	virtual void ReleaseWhiteKeys() const override final;
	virtual void AssignFinger(int16_t note, const char* fingers, bool leftHand) const override final;
private:
	class Keyboard2D_pimpl* pimpl_;

	virtual void AddKey(int16_t note) const override final;
	virtual void Draw(HDC) const override final;

	Keyboard3D(const Keyboard3D&) = delete;
	Keyboard3D(const Keyboard3D&&) = delete;
	Keyboard3D& operator=(const Keyboard3D&) = delete;
	Keyboard3D&& operator=(const Keyboard3D&&) = delete;
};