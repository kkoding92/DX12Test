#include "pch.h"
#include "Texture.h"

CTexture::CTexture()
{
	ZeroMemory(&m_tTexInfo, sizeof(TEXINFO));
}

CTexture::~CTexture()
{
	Release_Texture();
}

HRESULT CTexture::Insert_Texture(LPDIRECT3DDEVICE9 pGraphicDevice, const wstring& wstrFilePath)
{
	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_tTexInfo.tImageInfo)))
	{
		wstring wstrErrMsg = wstrFilePath + L"Load Failed!";
		MessageBox(nullptr, wstrErrMsg.c_str(), L"SystemError", MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFileEx(pGraphicDevice,
		wstrFilePath.c_str(),
		m_tTexInfo.tImageInfo.Width,
		m_tTexInfo.tImageInfo.Height,
		m_tTexInfo.tImageInfo.MipLevels,
		0,
		m_tTexInfo.tImageInfo.Format,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr, nullptr,
		&m_tTexInfo.pTexture)))
	{
		wstring wstrErrMsg = wstrFilePath + L"Create Texture Failed!";
		MessageBox(nullptr, wstrErrMsg.c_str(), L"SystemError", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

TEXINFO* CTexture::Get_Texture()
{
	return &m_tTexInfo;
}

void CTexture::Release_Texture()
{
	if (nullptr != m_tTexInfo.pTexture)
		m_tTexInfo.pTexture->Release();
}
