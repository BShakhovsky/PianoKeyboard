#pragma once
#pragma comment(lib, "Keyboard.lib")
class IKeyboard abstract
{
	IKeyboard() = delete;
protected:
	explicit IKeyboard(HWND, LPCTSTR path, bool isVolumeNormalized);
	virtual ~IKeyboard();
public:
	static constexpr int16_t minNote = 21, maxNote = 108;

	virtual void UpdateSize(UINT width, UINT height) = 0;

#pragma warning(push)
#pragma warning(disable:4514)	// unreferenced inline functions have been removed
	virtual void Restore3DPosition() const {}
	virtual void Zoom3D(int delta) const
	{
		UNREFERENCED_PARAMETER(delta);
	}
	virtual void Fit3DToWindow() const {}

	virtual void Move3DStart(int x, int y) const
	{
		UNREFERENCED_PARAMETER(x);
		UNREFERENCED_PARAMETER(y);
	}
	virtual void Rotate3DStart(int x, int y) const
	{
		UNREFERENCED_PARAMETER(x);
		UNREFERENCED_PARAMETER(y);
	}
	virtual void On3DMouseMove(int x, int y, bool move, bool rotate) const
	{
		UNREFERENCED_PARAMETER(x);
		UNREFERENCED_PARAMETER(y);
		UNREFERENCED_PARAMETER(move);
		UNREFERENCED_PARAMETER(rotate);
	}
#pragma warning(pop)

	void PressKey(const std::pair<int16_t, float>& note_volume);
	virtual void ReleaseKeys() const = 0;
	virtual void AssignFinger(int16_t note, const char* fingers, bool leftHand = false) const = 0;

	void Update(HDC hDC = nullptr) const;

	void NormalizeVolume(bool normalize = true) const;
protected:
	const HWND hWnd_;
private:
	virtual void AddKey(int16_t note) const = 0;
	virtual void Draw(HDC) const = 0;

	class Sound* sound_;
};
#include "Keyboard2D.h"
#include "Keyboard3D.h"