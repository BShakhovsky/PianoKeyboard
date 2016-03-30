#pragma once
#include "targetver.h"
#pragma warning(disable:4625 4626 4710 5026 5027)
#pragma warning(push)
#pragma warning(disable:4668 4820 5029)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WindowsX.h>

#include <DirectXTK\Audio.h>
#pragma comment(lib, "DirectXTK")

#include <boost\noncopyable.hpp>
#include <boost\lexical_cast.hpp>

#include <queue>
#pragma warning(pop)