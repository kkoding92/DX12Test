#include "pch.h"
#include "Transform.h"

CTransform::CTransform(void)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_matWorld);
}

CTransform::~CTransform(void)
{
}

INFO CTransform::Get_Info(void)
{
	return m_tInfo;
}

void CTransform::Set_Position(float fX, float fY)
{
	m_tInfo.fPosX = fX;
	m_tInfo.fPosY = fY;
}

void CTransform::Set_Scale(float fX, float fY)
{
	m_tInfo.fSizeX = fX;
	m_tInfo.fSizeY = fY;
}

D3DXMATRIX CTransform::Get_WorldMatrix()
{
	return m_matWorld;
}

void CTransform::Start_Component(void)
{
}

int CTransform::Update_Component(const float& fTimeDelta)
{
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, m_tInfo.fSizeX, m_tInfo.fSizeY, 1.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.fPosX, m_tInfo.fPosY, 0.f);
	m_matWorld = matScale * matTrans;

	return 0;
}

CTransform* CTransform::Create()
{
	CTransform* pInstance = new CTransform;

	if(nullptr != pInstance)
		pInstance->Start_Component();
	
	return pInstance;
}