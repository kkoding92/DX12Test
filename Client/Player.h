#pragma once

class CGraphicDevice;
class CTransform;
class CPlayer : public CGameObject
{
public:
	CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayer(void);

private:
	HRESULT			Add_Component(void);

public:
	void			Set_TexInfo(TEXINFO* pTexInfo) { m_pTexInfo = pTexInfo; }
	void			Set_DeviceClass(CGraphicDevice* pGraphicDevice) { m_pDeviceClass = pGraphicDevice; }

public:
	void			Start_GameObject(void) override;
	int				Update_GameObject(const float& fTimeDelta) override;
	void			LateUpdate_GameObject(const float& fTimeDelta) override;
	void			Render_GameObject(void) override;

private:
	CGraphicDevice*		m_pDeviceClass; // ��¿� ����� GraphicDevice Ŭ����
	TEXINFO*			m_pTexInfo;		// ����� �ؽ�ó 

	CTransform*			m_pTransform;	// Transform ������Ʈ
};

