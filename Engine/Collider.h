#pragma once

#include "Component.h"

class CCollider : public CComponent
{
private:
	explicit CCollider(void);
	virtual ~CCollider(void);

public:
	RECT		Get_Rect();
	void		Init_ColSize(float fSize);
	void		Render_Collider();

public:
	virtual void			Start_Component(void) override;
	virtual int				Update_Component(const float& fTimeDelta) override;

private:
	float		m_fColSize;
	RECT		m_tRect;

public:
	static	CCollider* Create();
};

