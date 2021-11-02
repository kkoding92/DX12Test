#pragma once

class CGraphicDevice;
class CTransform;
class CCollider;
class CKingJelly : public CGameObject
{
public:
	enum KJELLY_STATE { IDLE, FADEOUT, DIE, END };

public:
	CKingJelly(LPDIRECT3DDEVICE9 pGraphicDev);
	CKingJelly(const CKingJelly& rhs);
	virtual ~CKingJelly(void);

private:
	HRESULT			Add_Component(void);
	void			Update_State(const float& fTimeDelta);
	void			Change_State(void);

public:
	void			Start_GameObject(void) override;
	int				Update_GameObject(const float& fTimeDelta) override;
	void			LateUpdate_GameObject(const float& fTimeDelta) override;
	void			Render_GameObject(void) override;

public:
	CGameObject*	Clone(void) override;

private:
	CGraphicDevice* m_pDeviceClass;
	TEXINFO* m_pTexInfo;
	CTransform* m_pTransform;
	CCollider*  m_pCollider;

	KJELLY_STATE		m_eCurState;
	KJELLY_STATE		m_eNextState;

	float			m_fFadeSpeed;
	float			m_fTimer;
	float			m_fCurAlpha;
};

