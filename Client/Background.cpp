#include "stdafx.h"
#include "Background.h"

CBackground::CBackground(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CBackground::~CBackground(void)
{
}

void CBackground::Start_GameObject(void)
{
	m_pDeviceClass = CGraphicDevice::Get_Instance();
	m_pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"bg");

	Add_Component();

	m_pTransform->Set_Scale(2.f, 2.f);
	m_pTransform->Set_Position(700.f, 300.f);
}

int CBackground::Update_GameObject(const float& fTimeDelta)
{
	CGameObject::Update_GameObject(fTimeDelta);

	return 0;
}

void CBackground::LateUpdate_GameObject(const float& fTimeDelta)
{
}

void CBackground::Render_GameObject(void)
{
	if (nullptr == m_pTexInfo || nullptr == m_pTransform)
		return;

	float fCenterX = float(m_pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(m_pTexInfo->tImageInfo.Height >> 1);
	D3DXVECTOR3 vCenter = { fCenterX, fCenterY, 0.f };

	D3DXMATRIX matWorld = m_pTransform->Get_WorldMatrix();
	m_pDeviceClass->Get_Sprite()->SetTransform(&matWorld);
	m_pDeviceClass->Get_Sprite()->Draw(m_pTexInfo->pTexture,
		nullptr,
		&vCenter,
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

CGameObject* CBackground::Clone(void)
{
	return nullptr;
}

HRESULT CBackground::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTransform = CTransform::Create();
	if (nullptr != pComponent)
		m_mapComponents.emplace(make_pair("TransformComponent", pComponent));

	return S_OK;
}
