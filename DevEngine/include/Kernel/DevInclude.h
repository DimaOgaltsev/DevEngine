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
#pragma comment(lib, "d3d9.lib")

//d3dx9
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

//STL
#include <string>
#include <vector>

namespace dev
{
  static D3DXCOLOR    clearColor      =   D3DCOLOR_XRGB(153, 153, 255);
  static const char*  logFilename     =   "devEngine.log";
  static const char*  functionShader  =   "main";
  static const float  defaultSpeed    =   0.01f;
  static const float  defaultSens     =   0.1f;
}

#endif