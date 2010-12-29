#ifndef DEV_INCLUDE_H
#define DEV_INCLUDE_H

//debug include
#ifdef _DEBUG
  #define _CRTDBG_MAP_ALLOC
  #include <stdlib.h>
  #include <crtdbg.h>
#endif

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace dev
{

}

#endif