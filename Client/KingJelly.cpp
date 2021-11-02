#include "stdafx.h"
#include "KingJelly.h"

CKingJelly::CKingJelly(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CKingJelly::CKingJelly(const CKingJelly& rhs)
	: CGameObject(rhs.m_pGraphicDev)
	, m_pDeviceClass(rhs.m_pDeviceClass)
{
}


CKingJelly::~CKingJelly(void)
{
}

void CKingJelly::Start_GameObject(void)
{
	m_pDeviceClass = CGraphicDevice::Get_Instance();
	m_pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"king_jelly");

	Add_Component();

	m_pTransform->Set_Scale(1.5f, 1.5f);
	m_pTransform->Set_Position(float(rand() % 800 + 1), float(rand() % 600 + 1));

	m_fTimer = 0.f;
	m_fCurAlpha = 255.f;
	m_fFadeSpeed = 200.f;

	m_eCurState = KJELLY_STATE::IDLE;
	m_eNextState = KJELLY_STATE::IDLE;
}

int CKingJelly::Update_GameObject(const float& fTimeDelta)
{
	if (m_bDead)
		return -1;

	Update_State(fTimeDelta);

	CGameObject::Update_GameObject(fTimeDelta);

	return 0;
}

void CKingJelly::LateUpdate_GameObject(const float& fTimeDelta)
{
	Change_State();
}

void CKingJelly::Render_GameObject(void)
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
		D3DCOLOR_ARGB(static_cast<int>(m_fCurAlpha), 255, 255, 255));

	m_pCollider->Render_Collider();
}

CGameObject* CKingJelly::Clone(void)
{
	return new CKingJelly(*this);
}

HRESULT CKingJelly::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTransform = CTransform::Create();
	if (nullptr != pComponent)
		m_mapComponents.emplace(make_pair("TransformComponent", pComponent));


	pComponent = m_pCollider = CCollider::Create();
	if (nullptr != pComponent)
	{
		m_pCollider->Set_Owner(this);
		m_pCollider->Init_ColSize(50.f);
		m_mapComponents.emplace(make_pair("ColliderComponent", pComponent));
	}

	return S_OK;
}

void CKingJelly::Update_State(const float& fTimeDelta)
{
	switch (m_eCurState)
	{
	case CKingJelly::IDLE:
		m_fTimer += fTimeDelta;

		if (m_fTimer >= 2.f)
			m_eNextState = CKingJelly::FADEOUT;
		break;
	case CKingJelly::FADEOUT:
		m_fCurAlpha -= m_fFadeSpeed * fTimeDelta;

		if (m_fCurAlpha <= 1.0f)
		{
			m_fCurAlpha = 0.f;
			m_eNextState = CKingJelly::DIE;
		}
		break;
	case CKingJelly::DIE:
		break;
	}
}

void CKingJelly::Change_State(void)
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case CKingJelly::IDLE:
			break;
		case CKingJelly::FADEOUT:
			break;
		case CKingJelly::DIE:
			m_bDead = true;
			break;
		}

		m_eCurState = m_eNextState;
	}
}