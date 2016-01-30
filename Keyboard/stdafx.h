#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
//#pragma warning(disable:4514)
#pragma warning(push, 3)
#	include <Windows.h>
#	include <WindowsX.h>
#pragma warning(pop)

#pragma warning(disable:4625 4626 5026 5027)
#pragma warning(push, 3)
#	include <boost\noncopyable.hpp>
#pragma warning(pop)

#pragma warning(disable:4710)
#pragma warning(push, 2)
#	include <boost\lexical_cast.hpp>
#pragma warning(pop)

#include <cassert>
#include <memory>
#include <vector>