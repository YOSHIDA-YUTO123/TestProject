//===================================================
//
// ビルボードクラス [billboard.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "ObjectBase/billboard.h"
#include "Base/texture_manager.h"
#include "Base/manager.h"
#include "Base/renderer.h"

//===================================================
// コンストラクタ
//===================================================
CBillboard::CBillboard() : 
	m_transform(),
	m_vertexBuffer(),
	m_col(Const::WHITE),
	m_size(Const::VEC3_NULL),
	m_nTextureID(CTextureManager::INVALID_ID)
{
}

//===================================================
// デストラクタ
//===================================================
CBillboard::~CBillboard()
{
}

//===================================================
// 生成処理
//===================================================
CBillboard* CBillboard::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXCOLOR& col, const char* pTexturePath)
{
	CBillboard* pInstance = new CBillboard;

	Transform3D transformParam = {};

	transformParam.pos = pos;

	// データの設定
	pInstance->m_transform.SetParam(transformParam);
	pInstance->m_size = size * 0.5f;
	pInstance->m_col = col;
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
HRESULT CBillboard::Init(void)
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
	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(size.x, size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, 0.0f);

	// 法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
void CBillboard::Uninit(void)
{
	// 自分自身の破棄
	Release();
}

//===================================================
// 更新処理
//===================================================
void CBillboard::Update(void)
{
}

//===================================================
// 描画処理
//===================================================
void CBillboard::Draw(void)
{
	// マネージャー
	CManager& manager = CManager::Instance();

	// レンダラーの取得
	CRenderer* pRenderer = manager.GetRenderer();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャマネージャーの取得
	CTextureManager* pTextureManager = manager.GetTextureManager();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxScal;

	// ビューマトリックスを宣言
	D3DXMATRIX mtxView;

	// パラメータの取得
	Transform3D transformParam = m_transform.GetParam();

	// ビューマトリックスの取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// カメラの逆行列を設定
	transformParam.mtxWorld._11 = mtxView._11;
	transformParam.mtxWorld._12 = mtxView._21;
	transformParam.mtxWorld._13 = mtxView._31;
	transformParam.mtxWorld._21 = mtxView._12;
	transformParam.mtxWorld._22 = mtxView._22;
	transformParam.mtxWorld._23 = mtxView._32;
	transformParam.mtxWorld._31 = mtxView._13;
	transformParam.mtxWorld._32 = mtxView._23;
	transformParam.mtxWorld._33 = mtxView._33;

	// データの再設定
	m_transform.SetParam(transformParam);

	// ワールドマトリックスの設定
	m_transform.BindMatrix(pDevice);

	// 頂点バッファの設定
	m_vertexBuffer.Bind(pDevice);

	//テクスチャの設定
	pDevice->SetTexture(0, pTextureManager->GetAdress(m_nTextureID));

	// ライトの影響を受けない
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ライトをもとに戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//===================================================
// テクスチャのIDの設定
//===================================================
void CBillboard::SetTextureID(const char* pTexturePath)
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