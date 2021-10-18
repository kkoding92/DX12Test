#include "stdafx.h"
#include "Jelly.h"

CJelly::CJelly(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CJelly::~CJelly(void)
{
}

void CJelly::Start_GameObject(void)
{
	m_pDeviceClass = CGraphicDevice::Get_Instance();
	m_pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"jelly");

	Add_Component();

	m_pTransform->Set_Scale(1.f, 1.f);
	//m_pTransform->Set_Position(500.f, 300.f);

	//m_fInitY = m_pTransform->Get_Info().fPosY;
	m_fAmountOfMovement = 100.f;

	m_eCurState = JELLY_STATE::IDLE;
	m_eNextState = JELLY_STATE::UP;
}

int CJelly::Update_GameObject(const float& fTimeDelta)
{
	if (m_bDead)
		return -1;

	Update_State(fTimeDelta);
	
	CGameObject::Update_GameObject(fTimeDelta);

	return 0;
}

void CJelly::LateUpdate_GameObject(const float& fTimeDelta)
{
	Change_State();
}

void CJelly::Render_GameObject(void)
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

	m_pCollider->Render_Collider();
}

HRESULT CJelly::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTransform = CTransform::Create();
	if (nullptr != pComponent)
		m_mapComponents.emplace(make_pair("TransformComponent", pComponent));


	pComponent = m_pCollider = CCollider::Create();
	if (nullptr != pComponent)
	{
		m_pCollider->Set_Owner(this);
		m_pCollider->Init_ColSize(40.f);
		m_mapComponents.emplace(make_pair("ColliderComponent", pComponent));
	}

	return S_OK;
}

void CJelly::Update_State(const float& fTimeDelta)
{
	switch (m_eCurState)
	{
	case CJelly::IDLE:
		break;
	case CJelly::UP:
		m_pTransform->Move_Pos(D3DXVECTOR2(0.f, -1.f), 100.f, fTimeDelta);

		if (m_pTransform->Get_Info().fPosY <= m_fGoalPosY)
			m_eNextState = JELLY_STATE::WAIT;

		break;
	case CJelly::DOWN:
		m_pTransform->Move_Pos(D3DXVECTOR2(0.f, 1.f), 100.f, fTimeDelta);

		if (m_pTransform->Get_Info().fPosY >= m_fGoalPosY)
			m_eNextState = JELLY_STATE::WAIT;

		break;
	case CJelly::WAIT:
		m_fTimer += fTimeDelta;

		if (m_fTimer >= 0.5f)
			(m_ePrevState == JELLY_STATE::UP) ? m_eNextState = JELLY_STATE::DOWN : m_eNextState = JELLY_STATE::UP;
		break;
	}
}

void CJelly::Change_State(void)
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case CJelly::IDLE:
			break;
		case CJelly::UP:
			m_fGoalPosY = m_fInitY - m_fAmountOfMovement;
			break;
		case CJelly::DOWN:
			m_fGoalPosY = m_fInitY + m_fAmountOfMovement;
			break;
		case CJelly::WAIT:
			m_fTimer = 0.f;
			m_ePrevState = m_eCurState;
			break;
		}
		m_eCurState = m_eNextState;
	}
}

void CJelly::Set_InitPosition(float fX, float fY)
{
	m_pTransform->Set_Position(fX, fY);
	m_fInitY = m_pTransform->Get_Info().fPosY;
}
