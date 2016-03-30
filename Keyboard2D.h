#pragma once
#include "IKeyboard.h"

class Keyboard2D : public IKeyboard
{
	Keyboard2D() = delete;
public:
	explicit Keyboard2D(HWND, LPCTSTR path);
	virtual ~Keyboard2D() override final;

	virtual void UpdateSize(HWND, UINT width, UINT height) const override final;
	virtual void ReleaseWhiteKeys() const override final;
	virtual void AssignFinger(int16_t note, const char* fingers, bool leftHand) const override final;
private:
	class Keyboard2D_pimpl* pimpl_;

	virtual void AddKey(int16_t note) const override final;
	virtual void Draw(HDC) const override final;

	Keyboard2D(const Keyboard2D&) = delete;
	Keyboard2D(const Keyboard2D&&) = delete;
	Keyboard2D& operator=(const Keyboard2D&) = delete;
	Keyboard2D&& operator=(const Keyboard2D&&) = delete;
};