#include "pch.h"
#include "Texture_Manager.h"
#include "Texture.h"

CTexture_Manager::CTexture_Manager(LPDIRECT3DDEVICE9 pGraphicDevice)
{
	m_pGraphicDevice = pGraphicDevice;
}

CTexture_Manager::~CTexture_Manager()
{
    Release_Manager();
}

TEXINFO* CTexture_Manager::Get_TexInfo(const wstring& wstrObjecKey)
{
	auto iter_find = m_mapTexture.find(wstrObjecKey);
	if (iter_find == m_mapTexture.end())
		return nullptr;

	return m_mapTexture[wstrObjecKey]->Get_Texture();
}

HRESULT CTexture_Manager::Insert_Texture(const wstring& wstrFilePath, const wstring& wstrObjectKey)
{
	auto iter_find = m_mapTexture.find(wstrObjectKey);

	if (iter_find == m_mapTexture.end())
	{
		CTexture* pTexture = new CTexture;

		if (FAILED(pTexture->Insert_Texture(m_pGraphicDevice, wstrFilePath)))
		{
			MessageBox(nullptr, L"Insert Texture Failed", L"SystemError", MB_OK);
			return E_FAIL;
		}
		m_mapTexture.emplace(wstrObjectKey, pTexture);
	}
	else
	{
		MessageBox(nullptr, L"Texture already inserted", L"SystemError", MB_OK);
		return E_FAIL;
	}

    return S_OK;
}

void CTexture_Manager::Release_Manager()
{
	for (auto& rPair : m_mapTexture)
	{
		if (rPair.second)
		{
			delete rPair.second;
			rPair.second = nullptr;
		}
	}
	m_mapTexture.clear();
}

