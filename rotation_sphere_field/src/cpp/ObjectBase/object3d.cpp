//===================================================
//
// 3Dオブジェクトの描画クラス [object3d.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "ObjectBase/object3d.h"
#include "Base/texture_manager.h"
#include "Base/manager.h"
#include "Base/renderer.h"

//===================================================
// コンストラクタ
//===================================================
CObject3D::CObject3D() : 
	m_vertexBuffer(),
	m_transform(),
	m_col(Const::WHITE),
	m_nTextureID(CTextureManager::INVALID_ID)
{
}

//===================================================
// デストラクタ
//===================================================
CObject3D::~CObject3D()
{
}

//===================================================
// 生成処理
//===================================================
CObject3D* CObject3D::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const char* pTexturePath)
{
	CObject3D* pInstance = new CObject3D;

	Transform3D transformParam = {};

	transformParam.pos = pos;

	// パラメータの設定
	pInstance->m_transform.SetParam(transformParam);
	pInstance->m_size = size * 0.5f;
	pInstance->SetTextureID(pTexturePath);

	// 初期化処理
	if (FAILED(pInstance->Init()))
	{
		// 終了処理
		pInstance->Uninit();
		pInstance = nullptr;
		return nullptr;
	}
	return pInstance;
}

//===================================================
// 初期化処理
//===================================================
HRESULT CObject3D::Init(void)
{
	// 頂点バッファの生成
	if (FAILED(m_vertexBuffer.CreateBuffer(sizeof(VERTEX_3D), 4, FVF_VERTEX_3D)))
	{
		return E_FAIL;
	}

	// 頂点情報のポインタ
	VERTEX_3D* pVtx = nullptr;

	// 頂点バッファのロック
	if (FAILED(m_vertexBuffer.Lock((void**)&pVtx)))
	{
		return E_FAIL;
	}

	// 大きさの取得
	D3DXVECTOR3 size = m_size;

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
	pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, -size.z);
	pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, -size.z);

	// 法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファのアンロック
	m_vertexBuffer.UnLock();

	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CObject3D::Uninit(void)
{
	// 自分自身の破棄
	Release();
}

//===================================================
// 更新処理
//===================================================
void CObject3D::Update(void)
{
}

//===================================================
// 描画処理
//===================================================
void CObject3D::Draw(void)
{
	// マネージャー
	CManager& manager = CManager::Instance();

	// レンダラーの取得
	CRenderer* pRenderer = manager.GetRenderer();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャマネージャーの取得
	CTextureManager* pTextureManager = manager.GetTextureManager();

	// マトリックスの設定
	m_transform.BindMatrix(pDevice);

	// 頂点バッファの設定
	m_vertexBuffer.Bind(pDevice);

	// テクスチャ設定
	pDevice->SetTexture(0, pTextureManager->GetAdress(m_nTextureID));

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//===================================================
// テクスチャのIDの設定
//===================================================
void CObject3D::SetTextureID(const char* pTexturePath)
{
	// マネージャーの取得
	CManager& manager = CManager::Instance();

	// テクスチャマネージャーの取得
	CTextureManager* pTextureManager = manager.GetTextureManager();

	if (pTextureManager == nullptr)
	{
		return;
	}

	// IDの登録
	m_nTextureID = pTextureManager->Register(pTexturePath);
}
