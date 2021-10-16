#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{							  
}

CPlayer::~CPlayer(void)
{
}

void CPlayer::Start_GameObject(void)
{
	Add_Component();
	m_pTransform->Set_Scale(1.f, 1.f);
	m_pTransform->Set_Position(400.f, 300.f);
}

int CPlayer::Update_GameObject(const float& fTimeDelta)
{
	D3DXVECTOR2 vDir = { 0.f, 0.f };

	if (GetAsyncKeyState('W') & 0x8000)
		vDir = { 0.f, -1.f };
	else if (GetAsyncKeyState('S') & 0x8000)
		vDir = { 0.f, 1.f };
	else if (GetAsyncKeyState('A') & 0x8000)
		vDir = { -1.f, 0.f };
	else if (GetAsyncKeyState('D') & 0x8000)
		vDir = { 1.f, 0.f };

	m_pTransform->Move_Pos(vDir, 500.f, fTimeDelta);


	CGameObject::Update_GameObject(fTimeDelta);

	return 0;
}

void CPlayer::LateUpdate_GameObject(const float& fTimeDelta)
{
}

void CPlayer::Render_GameObject(void)
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

HRESULT CPlayer::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTransform = CTransform::Create();
	if (nullptr != pComponent)
		m_mapComponents.emplace(make_pair("TransformComponent", pComponent));

	return S_OK;
}

