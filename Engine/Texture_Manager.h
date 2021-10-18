#pragma once
class CTexture;
class CTexture_Manager
{
private:
	CTexture_Manager();
	~CTexture_Manager();

public:
	static CTexture_Manager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CTexture_Manager;
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
	TEXINFO*		Get_TexInfo(const wstring& wstrObjecKey);
	HRESULT			Insert_Texture(const wstring& wstrFilePath, const wstring& wstrObjectKey);
	void			Release_Manager();

private:
	map<wstring, CTexture*> m_mapTexture;
	//LPDIRECT3DDEVICE9		m_pGraphicDevice;

	static CTexture_Manager* m_pInstance;
};

