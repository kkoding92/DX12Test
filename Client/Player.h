#pragma once

class CGraphicDevice;
class CTransform;
class CCollider;
class CPlayer : public CGameObject
{
public:
	CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayer(void);

private:
	HRESULT			Add_Component(void);

public:
	void			Start_GameObject(void) override;
	int				Update_GameObject(const float& fTimeDelta) override;
	void			LateUpdate_GameObject(const float& fTimeDelta) override;
	void			Render_GameObject(void) override;

public:
	CGameObject*	Clone(void) override;

private:
	CGraphicDevice*		m_pDeviceClass; // 출력에 사용할 GraphicDevice 클래스
	TEXINFO*			m_pTexInfo;		// 출력할 텍스처 

	CTransform*			m_pTransform;	// Transform 컴포넌트
	CCollider*			m_pCollider;	// Collider 컴포넌트
};

