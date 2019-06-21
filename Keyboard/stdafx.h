#pragma once
#include "targetver.h"
#pragma warning(disable:4625 4626 4710 5026 5027)
#pragma warning(push)
#pragma warning(disable:4244 4365 4514 4571 4619 4643 4668 4774 4820 4917 5029 5039 5045)
#pragma warning(disable:26439 26495)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WindowsX.h>

#include <comdef.h>

#include <DirectXTK\Audio.h>
#if min(WINVER, _WIN32_WINNT) < _WIN32_WINNT_WIN8
#	pragma comment(lib, "DirectXTKAudioDX")
#else
#	pragma comment(lib, "DirectXTKAudioWin8")
#endif

#include <boost\noncopyable.hpp>
#include <boost\lexical_cast.hpp>

#include <queue>
#pragma warning(pop)