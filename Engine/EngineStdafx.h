#pragma once

#include <windows.h>
#include <memory.h>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>
#include <ctime>
#include <tchar.h>
#include <process.h>
#include <string>
using namespace std;

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "winmm")

typedef struct tagTextureInfomation
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO tImageInfo;
}TEXINFO;

#include "GraphicDevice.h"
#include "Texture_Manager.h"
#include "Timer.h"

//void Test();
