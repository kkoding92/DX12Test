#pragma once

class CGraphicDevice;
class CTransform;
class CBackground : public CGameObject
{
public:
	CBackground(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBackground(void); 

private:
	HRESULT			Add_Component(void);

public:
	void			Start_GameObject(void) override;
	int				Update_GameObject(const float& fTimeDelta) override;
	void			LateUpdate_GameObject(const float& fTimeDelta) override;
	void			Render_GameObject(void) override;

public:
	CGameObject* Clone(void) override;

private:
	CGraphicDevice* m_pDeviceClass;
	TEXINFO*		m_pTexInfo;
	CTransform*		m_pTransform;
};

