#pragma once
class CGraphicDevice
{
private:
	CGraphicDevice(void);
	~CGraphicDevice(void);

public:
	static CGraphicDevice* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CGraphicDevice;
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	LPDIRECT3DDEVICE9	Get_GraphicDev(void) { return m_pGraphicDev; }
	LPD3DXSPRITE		Get_Sprite() { return m_pSprite; }

public:
	HRESULT		Ready_GraphicDevice(HWND hWnd);

	void		Render_Begin(D3DXCOLOR Color);
	void		Render_End(void);

private:
	LPDIRECT3D9					m_pSDK;			// 컴 객체를 생성하는 모체
	LPDIRECT3DDEVICE9			m_pGraphicDev;	// 그리기를 위한 그래픽 컴 객체
	LPD3DXSPRITE				m_pSprite;

private:																
	static CGraphicDevice*		m_pInstance;	
};

