#include "stdafx.h"
#include "MainScene.h"
#include "Player.h"
#include "Jelly.h"

CMainScene::CMainScene()
{
}

CMainScene::~CMainScene()
{
}

void CMainScene::Create_GameObject()
{
	CGameObject* pObj = nullptr;
	LPDIRECT3DDEVICE9 pGraphicDevice = CGraphicDevice::Get_Instance()->Get_GraphicDev();

	pObj = new CPlayer(pGraphicDevice);
	if (nullptr != pObj)
	{
		pObj->Start_GameObject();
		Add_GameObject(OBJ_PLAYER, pObj);
	}

	for (int i = 1; i <= 3; ++i)
	{
		pObj = new CJelly(pGraphicDevice);
		if (nullptr != pObj)
		{
			pObj->Start_GameObject();
			dynamic_cast<CJelly*>(pObj)->Set_InitPosition(200.f * i, 300.f);
			Add_GameObject(OBJ_JELLY, pObj);
		}
	}
}

void CMainScene::Check_Collision()
{
	CGameObject* pPlayer = Get_Player();
	CCollider* pPlayerColliderCom = dynamic_cast<CCollider*>(pPlayer->Get_Component("ColliderComponent"));
	
	list<CGameObject*> pJellyList = Get_ObjectList(CScene::OBJ_JELLY);
	CCollider* pJellyColliderCom = nullptr;

	RECT rc = {};

	for (auto iter : pJellyList)
	{
		pJellyColliderCom = dynamic_cast<CCollider*>(iter->Get_Component("ColliderComponent"));

		if (pJellyColliderCom == nullptr)
			continue;

		RECT pPlayerRect = pPlayerColliderCom->Get_Rect();
		RECT pJellyRect = pJellyColliderCom->Get_Rect();

		if (IntersectRect(&rc, &pPlayerRect, &pJellyRect))
		{
			iter->Set_Dead();
		}
	}
}

void CMainScene::Start_Scene(void)
{
	Create_GameObject();
}

int CMainScene::Update_Scene(const float& fTimeDelta)
{
	CScene::Update_Scene(fTimeDelta);
	return 0;
}

void CMainScene::LateUpdate_Scene(const float& fTimeDelta)
{
	CScene::LateUpdate_Scene(fTimeDelta);

	Check_Collision();
}

void CMainScene::Render_Scene(void)
{
	CScene::Render_Scene();
}
