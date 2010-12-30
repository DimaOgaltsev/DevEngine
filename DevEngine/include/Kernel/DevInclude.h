#ifndef DEV_INCLUDE_H
#define DEV_INCLUDE_H

//debug include
#ifdef _DEBUG
  #define _CRTDBG_MAP_ALLOC
  #include <stdlib.h>
  #include <crtdbg.h>
#endif

//directX
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//STL
#include <string>
#include <vector>

namespace dev
{

}

#endif