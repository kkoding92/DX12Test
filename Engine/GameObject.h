#pragma once

#include "Component.h"

class CGameObject
{
public:
	CGameObject(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGameObject(void);

public:
	CComponent*		Get_Component(string strTag);
	void			Set_Dead() { m_bDead = true; }

public:
	virtual void			Start_GameObject(void);
	virtual int				Update_GameObject(const float& fTimeDelta);
	virtual void			LateUpdate_GameObject(const float& fTimeDelta);
	virtual void			Render_GameObject(void);

protected:
	LPDIRECT3DDEVICE9			m_pGraphicDev;
	map<string, CComponent*>	m_mapComponents; // ������Ʈ�� ���� �����̳�

	bool						m_bDead = false;
};

