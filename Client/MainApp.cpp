#include "stdafx.h"
#include "MainApp.h"

CMainApp::CMainApp(void)
	:m_pDeviceClass(nullptr)
	,m_pGraphicDevice(nullptr)
{
}

CMainApp::~CMainApp(void)
{
	Release_MainApp();
}

HRESULT CMainApp::Ready_MainApp(void)
{
	m_pDeviceClass = new CGraphicDevice;
	if (nullptr == m_pDeviceClass)
		return E_FAIL;

	if (E_FAIL == SetUp_Setting(&m_pGraphicDevice))
		return E_FAIL;

	m_pGraphicDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pGraphicDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	return S_OK;
}

int CMainApp::Update_MainApp(void)
{
	return 0;
}

void CMainApp::LateUpdate_MainApp(void)
{
}

void CMainApp::Render_MainApp(void)
{
	m_pDeviceClass->Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));

	// 그릴 것들 삽입
	//배경->Render();
	//캐릭터->Render();

	m_pDeviceClass->Render_End();
}

void CMainApp::Release_MainApp(void)
{
	if (nullptr != m_pDeviceClass)
	{
		delete m_pDeviceClass;
		m_pDeviceClass = nullptr;
	}
}


HRESULT CMainApp::SetUp_Setting(LPDIRECT3DDEVICE9* ppGraphicDev)
{
	if (E_FAIL == m_pDeviceClass->Ready_GraphicDevice(g_hWnd))
		return  E_FAIL;

	*ppGraphicDev = m_pDeviceClass->Get_GraphicDev();
	(*ppGraphicDev)->AddRef();

	return S_OK;
}
