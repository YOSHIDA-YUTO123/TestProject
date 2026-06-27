//===================================================
//
// インデックスバッファを使いやすくするクラス [index_buffer.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "Buffer/index_buffer.h"
#include "Base/manager.h"
#include "Base/renderer.h"

//===================================================
// コンストラクタ
//===================================================
CIndexBuffer::CIndexBuffer() : 
	m_pBuffer(nullptr)
{
}

//===================================================
// デストラクタ
//===================================================
CIndexBuffer::~CIndexBuffer()
{
	// インデックスバッファの破棄
	if (m_pBuffer != nullptr)
	{
		m_pBuffer->Release();
		m_pBuffer = nullptr;
	}
}

//===================================================
// 生成処理
//===================================================
HRESULT CIndexBuffer::Create(const int nNumIndex)
{
	// マネージャーの取得
	CManager& manager = CManager::Instance();

	// レンダラーの取得
	CRenderer* pRenderer = manager.GetRenderer();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// インデックスバッファの生成
	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * nNumIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pBuffer,
		NULL)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===================================================
// インデックスバッファのロック
//===================================================
HRESULT CIndexBuffer::Lock(void** ppData)
{
	// インデックスバッファのロック
	if (FAILED(m_pBuffer->Lock(0, 0, ppData, 0)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===================================================
// インデックスバッファのアンロック
//===================================================
HRESULT CIndexBuffer::UnLock()
{
	// インデックスバッファのアンロック
	if (FAILED(m_pBuffer->Unlock()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===================================================
// インデックスバッファのバインド
//===================================================
HRESULT CIndexBuffer::Bind(LPDIRECT3DDEVICE9 pDevice)
{
	// インデックスバッファをデータストリームに設定
	if (FAILED(pDevice->SetIndices(m_pBuffer)))
	{
		return E_FAIL;
	}

	return S_OK;
}
