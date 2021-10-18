#include "pch.h"
#include "Scene.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	for (size_t i = 0; i < OBJ_END; i++)
	{
		for (auto& pObject : m_listObject[i])
			delete pObject;

		m_listObject[i].clear();
	}
}

void CScene::Add_GameObject(OBJ_ID eID, CGameObject* pObject)
{
	if (nullptr == pObject || 0 > eID || eID >= OBJ_END)
		return;

	m_listObject[eID].emplace_back(pObject);
}

void CScene::Start_Scene(void)
{
}

int CScene::Update_Scene(const float& fTimeDelta)
{
	for (size_t i = OBJ_BG; i < OBJ_END; ++i)
	{
		for (auto iter = m_listObject[i].begin(); iter != m_listObject[i].end(); )
		{
			int iEvent = (*iter)->Update_GameObject(fTimeDelta);
			if (-1 == iEvent)
			{
				delete *iter;
				iter = m_listObject[i].erase(iter);
			}
			else
				++iter;
		}
	}
	return 0;
}

void CScene::LateUpdate_Scene(const float& fTimeDelta)
{
	for (size_t i = OBJ_BG; i < OBJ_END; ++i)
	{
		for (auto& pObject : m_listObject[i])
			pObject->LateUpdate_GameObject(fTimeDelta);
	}
}

void CScene::Render_Scene(void)
{
	for (size_t i = OBJ_BG; i < OBJ_END; ++i)
	{
		for (auto& pObject : m_listObject[i])
			pObject->Render_GameObject();
	}
}
