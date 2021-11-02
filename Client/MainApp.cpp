#include "stdafx.h"
#include "MainApp.h"
#include "MainScene.h"
//#include "Player.h"
//#include "Jelly.h"

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
	m_pDeviceClass = CGraphicDevice::Get_Instance();
	if (nullptr == m_pDeviceClass)
		return E_FAIL;

	if (E_FAIL == SetUp_Setting(&m_pGraphicDevice))
		return E_FAIL;

	m_pTextureManager = CTexture_Manager::Get_Instance();
	if (nullptr == m_pTextureManager)
		return E_FAIL;

	if (E_FAIL == Add_Resource())
		return E_FAIL;

	m_pScene = new CMainScene;
	if (nullptr != m_pScene)
		m_pScene->Start_Scene();

	//Add_GameObject();

	m_pGraphicDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pGraphicDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	return S_OK;
}

int CMainApp::Update_MainApp(const float& fTimeDelta)
{
	m_pScene->Update_Scene(fTimeDelta);
	//m_pPlayer->Update_GameObject(fTimeDelta);
	//m_pJelly->Update_GameObject(fTimeDelta);
	//m_pJelly2->Update_GameObject(fTimeDelta);
	//m_pJelly3->Update_GameObject(fTimeDelta);
	return 0;
}

void CMainApp::LateUpdate_MainApp(const float& fTimeDelta)
{
	m_pScene->LateUpdate_Scene(fTimeDelta);
	//m_pPlayer->LateUpdate_GameObject(fTimeDelta);
	//m_pJelly->LateUpdate_GameObject(fTimeDelta);
	//m_pJelly2->LateUpdate_GameObject(fTimeDelta);
	//m_pJelly3->LateUpdate_GameObject(fTimeDelta);
}

void CMainApp::Render_MainApp(void)
{
	m_pDeviceClass->Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));

	m_pScene->Render_Scene();
	//m_pPlayer->Render_GameObject();
	//m_pJelly->Render_GameObject();
	//m_pJelly2->Render_GameObject();
	//m_pJelly3->Render_GameObject();

	m_pDeviceClass->Render_End();
}

void CMainApp::Release_MainApp(void)
{
	//if (nullptr != m_pPlayer)
	//{
	//	delete m_pPlayer;
	//	m_pPlayer = nullptr;
	//}

	//if (nullptr != m_pJelly)
	//{
	//	delete m_pJelly;
	//	m_pJelly = nullptr;
	//}

	if (nullptr != m_pScene)
	{
		delete m_pScene;
		m_pScene = nullptr;
	}
	
	m_pDeviceClass->Destroy_Instance();
	m_pTextureManager->Destroy_Instance();
}	


HRESULT CMainApp::SetUp_Setting(LPDIRECT3DDEVICE9* ppGraphicDev)
{
	if (E_FAIL == m_pDeviceClass->Ready_GraphicDevice(g_hWnd))
		return  E_FAIL;

	*ppGraphicDev = m_pDeviceClass->Get_GraphicDev();
	(*ppGraphicDev)->AddRef();

	return S_OK;
}

HRESULT CMainApp::Add_Resource()
{
	if (E_FAIL == m_pTextureManager->Insert_Texture(L"../Texture/cookie.png", L"cookie"))
		return E_FAIL;

	if (E_FAIL == m_pTextureManager->Insert_Texture(L"../Texture/jelly.png", L"jelly"))
		return E_FAIL;

	if (E_FAIL == m_pTextureManager->Insert_Texture(L"../Texture/king_jelly.png", L"king_jelly"))
		return E_FAIL;

	if (E_FAIL == m_pTextureManager->Insert_Texture(L"../Texture/background.png", L"bg"))
		return E_FAIL;

	return S_OK;
}
