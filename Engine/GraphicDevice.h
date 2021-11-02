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
	LPD3DXLINE			Get_Line() { return m_pLine; }
	LPD3DXFONT			Get_Font() { return m_pFont; }

public:
	HRESULT		Ready_GraphicDevice(HWND hWnd);

	void		Render_Begin(D3DXCOLOR Color);
	void		Render_End(void);

private:
	LPDIRECT3D9					m_pSDK;			// �� ��ü�� �����ϴ� ��ü
	LPDIRECT3DDEVICE9			m_pGraphicDev;	// �׸��⸦ ���� �׷��� �� ��ü
	LPD3DXSPRITE				m_pSprite;
	LPD3DXLINE					m_pLine;
	LPD3DXFONT					m_pFont;

private:																
	static CGraphicDevice*		m_pInstance;	
};

