#include "pch.h"
#include "Collider.h"

CCollider::CCollider(void)
	: m_fColSize(1.f)
{
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CCollider::~CCollider(void)
{
}

RECT CCollider::Get_Rect()
{
	return m_tRect;
}

void CCollider::Init_ColSize(float fSize)
{
	m_fColSize = fSize;
}

void CCollider::Render_Collider()
{
	D3DXVECTOR2 vLine[5] = {
		{ static_cast<float>(m_tRect.left), static_cast<float>(m_tRect.top) },
		{ static_cast<float>(m_tRect.right), static_cast<float>(m_tRect.top) },
		{ static_cast<float>(m_tRect.right), static_cast<float>(m_tRect.bottom) },
		{ static_cast<float>(m_tRect.left) , static_cast<float>(m_tRect.bottom) },
		{ static_cast<float>(m_tRect.left), static_cast<float>(m_tRect.top) },
	};

	CGraphicDevice::Get_Instance()->Get_Sprite()->End();
	CGraphicDevice::Get_Instance()->Get_Line()->SetWidth(2.f);
	CGraphicDevice::Get_Instance()->Get_Line()->Draw(vLine, 5, D3DCOLOR_ARGB(255, 0, 255, 0));
	CGraphicDevice::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
}

void CCollider::Start_Component(void)
{
}

int CCollider::Update_Component(const float& fTimeDelta)
{
	CTransform* pTransComponent = dynamic_cast<CTransform*>(m_pOwner->Get_Component("TransformComponent"));
	if (pTransComponent == nullptr)
		return 0;

	INFO tInfo = pTransComponent->Get_Info();

	float fCenterX = tInfo.fPosX;
	float fCenterY = tInfo.fPosY;

	long left = 0;
	long top = 0;
	long right = 0;
	long bottom = 0;

	left = long(fCenterX - m_fColSize * 0.5f);
	top = long(fCenterY - m_fColSize * 0.5f);
	right = long(fCenterX + m_fColSize * 0.5f);
	bottom = long(fCenterY + m_fColSize * 0.5f);

	m_tRect = { left, top, right, bottom };

	return 0;
}

CCollider* CCollider::Create()
{
	CCollider* pInstance = new CCollider;

	if (nullptr != pInstance)
		pInstance->Start_Component();

	return pInstance;
}
