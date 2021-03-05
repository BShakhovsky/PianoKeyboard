#pragma once
#include "targetver.h"
#pragma warning(disable:4625 4626 4710 5026 5027)
#pragma warning(push)
#pragma warning(disable:4244 4365 4514 4571 4619 4643 4668 4774 4820 4917 5029 5039 5045 5219)
#pragma warning(disable:26439 26495 26812 26819)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WindowsX.h>

//#include <comdef.h>

#if min(WINVER, _WIN32_WINNT) < _WIN32_WINNT_WIN8
/* From https://www.nuget.org/packages/directxtk_desktop_2015/2019.12.17.1:
To support Windows 7, you need to build DirectXTKAudioDX.lib using the legacy DirectX SDK and deploy it via the legacy DXSETUP

In the latest DirectXTK: Retired XAudio 2.7 for DirectX Tool Kit for Audio
So, have to download from old release: https://github.com/microsoft/DirectXTK/tree/may2020 */
#	include <DirectXTK-may2020/Audio.h>
#	pragma comment(lib, "DirectXTKAudioDX")
#else
#	include <DirectXTK/Audio.h>
//#	pragma comment(lib, "DirectXTKAudioWin8")
#endif

#include <boost\noncopyable.hpp>
#include <boost\lexical_cast.hpp>

#include <queue>
#pragma warning(pop)