#pragma once

#define WIN32_EXTRA_LEAN
#define WIN32_LEAN_AND_MEAN

#define NOSERVICE
#define NOMCX
#define NOIME
#define NOSOUND
#define NOCOMM
#define NOKANJI
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
#define NOMINMAX
#define NODRAWTEXT
#define NOBITMAP
#define NOHELP

#define STRICT

#define UNICODE
#define _UNICODE

////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#if defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <intrin.h>

////////////////////////////////////////////////////////////////////////////////

#include <winsdkver.h>
#include <sdkddkver.h>
#include <windows.h>
#include <windowsx.h>

#include <tchar.h>
#include <dbghelp.h>

#include <wrl.h>
using namespace Microsoft::WRL;

#include <comdef.h>

////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <chrono>
#include <concepts>
#include <deque>
#include <filesystem>
#include <fstream>
#include <functional>
#include <future>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <sstream>
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <string_view>
#include <map>
#include <malloc.h>
#include <memory>
#include <mutex>
#include <new>
#include <optional>
#include <set>
#include <span>
#include <queue>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>
#include <thread>
#include <tuple>
#include <typeinfo>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////

namespace Mockup
{
#ifdef _DEBUG
	constexpr bool cMockupMode_Debug = true;
#else
	constexpr bool cMockupMode_Debug = false;
#endif
}

////////////////////////////////////////////////////////////////////////////////

//#include "cista/serialization.h"

#include "utils/allign.hpp"
#include "async/synchron.hpp"
#include "container/ring.hpp"
#include "reflection/type.hpp"
#include "singleton/singleton.hpp"

//TODO
//#include "filesystem/dataset.hpp"
//#include "filesystem/entry.hpp"

#include "logger/sink.hpp"
#include "logger/logger.hpp"

//TODO
//#include "parallel/future.hpp"
//#include "parallel/task.hpp"
//#include "parallel/executor.hpp"
//#include "parallel/scheduler.hpp"

#include "platform/console.hpp"
#include "platform/window.hpp"

#include "timer/timer.hpp"

////////////////////////////////////////////////////////////////////////////////