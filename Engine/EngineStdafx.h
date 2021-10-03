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

typedef struct tagTransformInfo
{
	float fPosX, fPosY;
	float fSizeX, fSizeY;
}INFO;

#include "GraphicDevice.h"
#include "Texture_Manager.h"
#include "Timer.h"

#include "GameObject.h"
#include "Transform.h"



//void Test();


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef _AFX
#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 
#endif // !_AFX

#endif
