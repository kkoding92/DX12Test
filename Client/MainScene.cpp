#include "stdafx.h"
#include "MainScene.h"
#include "Player.h"
#include "Jelly.h"
#include "KingJelly.h"
#include "Background.h"

CMainScene::CMainScene()
{
}

CMainScene::~CMainScene()
{
	delete m_pBaseJelly;
	delete m_pBaseKingJelly;
}

void CMainScene::Create_GameObject()
{
	CGameObject* pObj = nullptr;
	LPDIRECT3DDEVICE9 pGraphicDevice = CGraphicDevice::Get_Instance()->Get_GraphicDev();

	pObj = new CBackground(pGraphicDevice);
	if (nullptr != pObj)
	{
		pObj->Start_GameObject();
		Add_GameObject(OBJ_BG, pObj);
	}

	pObj = new CPlayer(pGraphicDevice);
	if (nullptr != pObj)
	{
		pObj->Start_GameObject();
		Add_GameObject(OBJ_PLAYER, pObj);
	}

	srand((unsigned int)time(NULL));

	m_pBaseJelly = new CJelly(pGraphicDevice);
	m_pBaseKingJelly = new CKingJelly(pGraphicDevice);

	for (int i = 1; i <= 3; ++i)
	{
		pObj = m_pBaseJelly->Clone();

		if (nullptr != pObj)
		{
			pObj->Start_GameObject();
			dynamic_cast<CJelly*>(pObj)->Set_InitPosition(200.f * i, 300.f);
			Add_GameObject(OBJ_JELLY, pObj);
		}

		pObj = m_pBaseKingJelly->Clone();

		if (nullptr != pObj)
		{
			pObj->Start_GameObject();
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
			if(nullptr != dynamic_cast<CJelly*>(iter))
				m_iJellyCount += 10;
			else
				m_iJellyCount += 20;

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

	RECT rc = { 30, 30, 300, 200 };
	TCHAR szBuf[MAX_PATH] = L"";
	swprintf_s(szBuf, L"획득 점수 : %d", m_iJellyCount);
	CGraphicDevice::Get_Instance()->Get_Font()->DrawTextW(nullptr, 
															szBuf,								//출력 문자열
															lstrlen(szBuf),						//문자열 길이
															&rc,								//출력 영역
															0, 
															D3DCOLOR_ARGB(255, 255, 255, 255));	//글자 색
}
