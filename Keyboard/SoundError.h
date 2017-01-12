#pragma once
#include "DxError.h"

class SoundError : public DxError
{
public:
#pragma warning(push)
#pragma warning(disable:4514)	// unreferenced inline function has been removed
	SoundError() = default;
	explicit SoundError(const char* msg) : DxError(msg) {}
	explicit SoundError(const wchar_t* rusMsg) : DxError(rusMsg) {}
#pragma warning(pop)
};