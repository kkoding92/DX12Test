#pragma once

#include "Component.h"

class CTransform : public CComponent
{
private:
	explicit CTransform(void);
	virtual ~CTransform(void);

public:
	INFO			Get_Info(void);
	void			Set_Position(float fX, float fY);
	void			Set_Scale(float fX, float fY);
	void			Move_Pos(D3DXVECTOR2 vDir, const float& fMoveSpeed, const float& fTimeDelta);

	D3DXMATRIX		Get_WorldMatrix();

public:
	virtual void			Start_Component(void) override;
	virtual int				Update_Component(const float& fTimeDelta) override;

private:
	INFO		m_tInfo;
	D3DXMATRIX	m_matWorld;

public:
	static	CTransform*		Create();
};

