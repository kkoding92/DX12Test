#pragma once

class CGraphicDevice;
class CTransform;
class CCollider;
class CJelly : public CGameObject
{
public:
	enum JELLY_STATE{ IDLE, UP, DOWN, WAIT, END };

public:
	CJelly(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CJelly(void);

private:
	HRESULT			Add_Component(void);
	void			Update_State(const float& fTimeDelta);
	void			Change_State(void);

public:
	void			Set_InitPosition(float fX, float fY);

public:
	void			Start_GameObject(void) override;
	int				Update_GameObject(const float& fTimeDelta) override;
	void			LateUpdate_GameObject(const float& fTimeDelta) override;
	void			Render_GameObject(void) override;

private:
	CGraphicDevice* m_pDeviceClass; 
	TEXINFO*		m_pTexInfo;	
	CTransform*		m_pTransform;	
	CCollider*		m_pCollider;

	JELLY_STATE		m_eCurState;
	JELLY_STATE		m_eNextState;
	JELLY_STATE		m_ePrevState;

	float			m_fInitY; //초기 Y값
	float			m_fAmountOfMovement; // 움직임량
	float			m_fGoalPosY; //목표 Y값
	float			m_fTimer; //시간 체크
};

