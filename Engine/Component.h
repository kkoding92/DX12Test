#pragma once

#include "EngineStdafx.h"

class CGameObject;
class CComponent
{
public:
	CComponent(void);
	virtual ~CComponent(void);

public:
	void			Set_Owner(CGameObject* pObj);
	CGameObject*	Get_Owner(void);

public:
	virtual void			Start_Component(void);
	virtual int				Update_Component(const float& fTimeDelta);

protected:
	CGameObject*	m_pOwner;	// 해당 컴포넌트를 소유하고 있는 개체
};

