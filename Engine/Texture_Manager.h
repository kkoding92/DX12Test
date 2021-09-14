#pragma once
class CTexture;
class CTexture_Manager
{
public:
	CTexture_Manager(LPDIRECT3DDEVICE9 pGraphicDevice);
	~CTexture_Manager();

public:
	TEXINFO*		Get_TexInfo(const wstring& wstrObjecKey);
	HRESULT			Insert_Texture(const wstring& wstrFilePath, const wstring& wstrObjectKey);
	void			Release_Manager();

private:
	map<wstring, CTexture*> m_mapTexture;
	LPDIRECT3DDEVICE9		m_pGraphicDevice;
};

