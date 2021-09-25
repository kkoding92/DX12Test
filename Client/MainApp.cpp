#include "stdafx.h"
#include "MainApp.h"

CMainApp::CMainApp(void)
	:m_pDeviceClass(nullptr)
	,m_pGraphicDevice(nullptr)
	,m_pTextureManager(nullptr)
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

	m_pTextureManager = new CTexture_Manager(m_pGraphicDevice);
	if (nullptr == m_pTextureManager)
		return E_FAIL;

	if (E_FAIL == m_pTextureManager->Insert_Texture(L"../Texture/cookie.png", L"cookie"))
		return E_FAIL;

	m_pGraphicDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pGraphicDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	return S_OK;
}

int CMainApp::Update_MainApp(const float& fTimeDelta)
{
	m_fTimer += fTimeDelta;
	if (m_fTimer >= 3.f)
		m_bDraw = true;

	return 0;
}

void CMainApp::LateUpdate_MainApp(const float& fTimeDelta)
{
}

void CMainApp::Render_MainApp(void)
{
	m_pDeviceClass->Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));

	if (m_bDraw)
	{
		TEXINFO* pTexInfo = m_pTextureManager->Get_TexInfo(L"cookie");
		if (nullptr == pTexInfo)
			return;

		D3DXMATRIX matScale, matTrans, matWorld;
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);
		matWorld = matScale * matTrans;

		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);
		D3DXVECTOR3 vCenter = { fCenterX, fCenterY, 0.f };

		m_pDeviceClass->Get_Sprite()->SetTransform(&matWorld);
		m_pDeviceClass->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&vCenter,
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	m_pDeviceClass->Render_End();
}

void CMainApp::Release_MainApp(void)
{
	if (nullptr != m_pDeviceClass)
	{
		delete m_pDeviceClass;
		m_pDeviceClass = nullptr;
	}

	if (nullptr != m_pTextureManager)
	{
		delete m_pTextureManager;
		m_pTextureManager = nullptr;
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
