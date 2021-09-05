#pragma once
class CGraphicDevice
{
public:
	CGraphicDevice(void);
	~CGraphicDevice(void);

public:
	LPDIRECT3DDEVICE9 Get_GraphicDev(void) { return m_pGraphicDev; }

public:
	HRESULT		Ready_GraphicDevice(HWND hWnd);

	void		Render_Begin(D3DXCOLOR Color);
	void		Render_End(void);

private:
	LPDIRECT3D9					m_pSDK;			// �� ��ü�� �����ϴ� ��ü
	LPDIRECT3DDEVICE9			m_pGraphicDev;	// �׸��⸦ ���� �׷��� �� ��ü
};

