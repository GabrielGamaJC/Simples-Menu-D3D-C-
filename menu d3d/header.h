// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "detour\include\detours.h"


#pragma comment(lib, "detour\\lib.X86\\detours.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
// reference additional headers your program requires here
