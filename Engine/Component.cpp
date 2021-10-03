#include "pch.h"
#include "Component.h"

CComponent::CComponent(void)
	: m_pOwner(nullptr)
{
}

CComponent::~CComponent(void)
{
}

void CComponent::Set_Owner(CGameObject* pObj)
{
	if (nullptr != pObj)
		m_pOwner = pObj;
}

CGameObject* CComponent::Get_Owner(void)
{
	return m_pOwner;
}

void CComponent::Start_Component(void)
{
}

int CComponent::Update_Component(const float& fTimeDelta)
{
	return 0;
}

