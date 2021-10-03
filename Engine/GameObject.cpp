#include "pch.h"
#include "GameObject.h"

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pGraphicDev)
	:m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev->AddRef();
}

CGameObject::~CGameObject(void)
{
	m_pGraphicDev->Release();

	for (auto& iter : m_mapComponents)
	{
		delete iter.second;
		iter.second = nullptr;
	}
	m_mapComponents.clear();
}

CComponent* CGameObject::Get_Component(string strTag)
{
	auto iter = m_mapComponents.find(strTag);

	if (iter == m_mapComponents.end())
		return nullptr;

	return iter->second;
}

void CGameObject::Start_GameObject(void)
{
}

int CGameObject::Update_GameObject(const float& fTimeDelta)
{
	for (auto& iter : m_mapComponents)
		iter.second->Update_Component(fTimeDelta);

	return 0;
}

void CGameObject::LateUpdate_GameObject(const float& fTimeDelta)
{
}

void CGameObject::Render_GameObject(void)
{
}
