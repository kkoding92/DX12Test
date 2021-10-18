#pragma once

class CMainScene;
class CGraphicDevice;
class CMainApp
{
public:
	explicit CMainApp(void);
	~CMainApp(void);

public:
	HRESULT		Ready_MainApp(void);
	int			Update_MainApp(const float& fTimeDelta);
	void		LateUpdate_MainApp(const float& fTimeDelta);
	void		Render_MainApp(void);
	void		Release_MainApp(void);

private:
	HRESULT		SetUp_Setting(LPDIRECT3DDEVICE9* ppGraphicDev);
	HRESULT		Add_Resource();

private:
	CGraphicDevice*			m_pDeviceClass;
	CTexture_Manager*		m_pTextureManager;

	LPDIRECT3DDEVICE9		m_pGraphicDevice;

	CMainScene*				m_pScene;
};


