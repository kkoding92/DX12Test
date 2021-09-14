#pragma once
class CTexture
{
public:
	explicit CTexture();
	~CTexture();

public:
	HRESULT		Insert_Texture(LPDIRECT3DDEVICE9 pGraphicDevice, const wstring& wstrFilePath);
	TEXINFO*	Get_Texture();
	void		Release_Texture();

private:
	TEXINFO		m_tTexInfo;
};

