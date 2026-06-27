//===================================================
//
// 頂点バッファを使いやすくするクラス [vertex_buffer.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "Buffer/vertex_buffer.h"
#include "Base/manager.h"
#include "Base/renderer.h"

//===================================================
// コンストラクタ
//===================================================
CVertexBuffer::CVertexBuffer() : 
	m_pBuffer(nullptr)
{
}

//===================================================
// デストラクタ
//===================================================
CVertexBuffer::~CVertexBuffer()
{
	// 頂点バッファの破棄
	if (m_pBuffer != nullptr)
	{
		m_pBuffer->Release();
		m_pBuffer = nullptr;
	}
}

//===================================================
// 頂点バッファの生絵師
//===================================================
HRESULT CVertexBuffer::CreateBuffer(const UINT stride, const UINT numVertex, DWORD fvf)
{
	// レンダラーの取得
	CRenderer *pRenderer = CManager::Instance().GetRenderer();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファの生成・頂点情報の設定
	if (FAILED(pDevice->CreateVertexBuffer(stride * numVertex,
		D3DUSAGE_WRITEONLY,
		fvf,
		D3DPOOL_MANAGED,
		&m_pBuffer,
		NULL)))
	{
		return E_FAIL;
	}

	m_stride = stride;
	m_fvf = fvf;

	return S_OK;
}

//===================================================
// ロック
//===================================================
HRESULT CVertexBuffer::Lock(void** ppData)
{
	// 頂点バッファのロック
	if (FAILED(m_pBuffer->Lock(0, 0, ppData, 0)))
	{
		return E_FAIL;
	}
	return S_OK;
}

//===================================================
// アンロック
//===================================================
HRESULT CVertexBuffer::UnLock(void)
{
	// アンロック
	if (FAILED(m_pBuffer->Unlock()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===================================================
// ストリームソースの設定
//===================================================
HRESULT CVertexBuffer::Bind(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pBuffer, 0, m_stride);

	// 頂点フォーマットの設定
	pDevice->SetFVF(m_fvf);

	return S_OK;
}
