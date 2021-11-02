#include "pch.h"
#include "GraphicDevice.h"

CGraphicDevice* CGraphicDevice::m_pInstance = nullptr;

CGraphicDevice::CGraphicDevice(void)
	: m_pSDK(nullptr)
	, m_pGraphicDev(nullptr)
	, m_pSprite(nullptr)
	, m_pLine(nullptr)
	, m_pFont(nullptr)
{

}

CGraphicDevice::~CGraphicDevice(void)
{
	m_pLine->Release();
	m_pFont->Release();
	m_pSprite->Release();
	m_pGraphicDev->Release();
	m_pSDK->Release();
}

HRESULT CGraphicDevice::Ready_GraphicDevice(HWND hWnd)
{
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	if (nullptr == m_pSDK)
		return E_FAIL;

	D3DCAPS9			DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	if (E_FAIL == m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps))
		return E_FAIL;

	unsigned long	uFlag = 0L;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		uFlag |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	else
		uFlag |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	D3DPRESENT_PARAMETERS			Present_Parameters;
	ZeroMemory(&Present_Parameters, sizeof(D3DPRESENT_PARAMETERS));

	Present_Parameters.BackBufferWidth = 800; //ȭ�� ���� ������
	Present_Parameters.BackBufferHeight = 600; //ȭ�� ���� ������
	Present_Parameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	Present_Parameters.BackBufferCount = 1;

	Present_Parameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	Present_Parameters.MultiSampleQuality = 0;

	Present_Parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Present_Parameters.hDeviceWindow = hWnd;

	Present_Parameters.Windowed = 1;	// â ���1, ��üȭ�� ��� 0

	Present_Parameters.EnableAutoDepthStencil = TRUE;
	Present_Parameters.AutoDepthStencilFormat = D3DFMT_D24S8;

	Present_Parameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	Present_Parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// �׷��� ����̽� �İ�ü ����
	if (E_FAIL == m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, uFlag,
		&Present_Parameters, &m_pGraphicDev))
		return E_FAIL;

	if (E_FAIL == D3DXCreateSprite(m_pGraphicDev, &m_pSprite))
	{
		MessageBox(nullptr, L"m_pSprite Creating Failed", L"SystemError", MB_OK);
		return E_FAIL;
	}

	if (E_FAIL == D3DXCreateLine(m_pGraphicDev, &m_pLine))
	{
		MessageBox(nullptr, L"m_pLine Creating Failed", L"SystemError", MB_OK);
		return E_FAIL;
	}

	D3DXFONT_DESCW tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));
	tFontInfo.Height = 20;	// ����
	tFontInfo.Width = 10;	// ��
	tFontInfo.Weight = FW_LIGHT; //����
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"�������"); //�۾�ü

	if (E_FAIL == D3DXCreateFontIndirect(m_pGraphicDev, &tFontInfo, &m_pFont))
	{
		MessageBox(nullptr, L"m_pFont Creating Failed", L"SystemError", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void CGraphicDevice::Render_Begin(D3DXCOLOR Color)
{
	m_pGraphicDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, Color, 1.f, 0);
	m_pGraphicDev->BeginScene();

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CGraphicDevice::Render_End(void)
{
	m_pSprite->End();
	m_pGraphicDev->EndScene();
	m_pGraphicDev->Present(NULL, NULL, NULL, NULL);
}

