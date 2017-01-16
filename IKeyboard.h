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

	virtual void UpdateSize(HWND, UINT width, UINT height) = 0;

	void PressKey(const std::pair<int16_t, float>& note_volume);
	virtual void ReleaseKeys() const = 0;
	virtual void AssignFinger(int16_t note, const char* fingers, bool leftHand = false) const = 0;

	void Update(HDC hDC = nullptr) const;

	void NormalizeVolume(bool normalize = true) const;
private:
	virtual void AddKey(int16_t note) const = 0;
	virtual void Draw(HDC) const = 0;

	class Sound* sound_;
};

#include "Keyboard2D.h"
#include "Keyboard3D.h"