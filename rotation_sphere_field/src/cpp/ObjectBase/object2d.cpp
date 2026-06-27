//===================================================
//
// 2Dオブジェクトの描画クラス [object2d.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "ObjectBase\object2d.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/texture_manager.h"

//===================================================
// コンストラクタ
//===================================================
CObject2D::CObject2D() : 
	m_vertexBuffer(),
	m_transform(),
	m_col(Const::WHITE),
	m_nTextureID(CTextureManager::INVALID_ID)
{
}

//===================================================
// デストラクタ
//===================================================
CObject2D::~CObject2D()
{
}

//===================================================
// 生成処理
//===================================================
CObject2D* CObject2D::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	CObject2D* pInstance = new CObject2D;

	Transform2D transformParam = {};

	transformParam.pos = pos;
	transformParam.size = size * 0.5f;

	// パラメータの設定
	pInstance->m_transform.SetParam(transformParam);

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
HRESULT CObject2D::Init(void)
{
	// 頂点バッファの生成
	if (FAILED(m_vertexBuffer.CreateBuffer(sizeof(VERTEX_2D), 4, FVF_VERTEX_2D)))
	{
		return E_FAIL;
	}

	// パラメータの取得
	Transform2D transformParam = m_transform.GetParam();

	// 頂点情報のポインタ
	VERTEX_2D* pVtx = nullptr;

	// 頂点バッファのロック
	if (FAILED(m_vertexBuffer.Lock((void**)&pVtx)))
	{
		return E_FAIL;
	}

	float fLength = sqrtf((transformParam.size.x * transformParam.size.x) + (transformParam.size.y * transformParam.size.y));
	float fAngle = atan2f(transformParam.size.x, transformParam.size.y);

	// 頂点座標の設定
	pVtx[0].pos.x = transformParam.pos.x + sinf(transformParam.fAngle - (D3DX_PI - fAngle)) * fLength;
	pVtx[0].pos.y = transformParam.pos.y + cosf(transformParam.fAngle - (D3DX_PI - fAngle)) * fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = transformParam.pos.x + sinf(transformParam.fAngle + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.y = transformParam.pos.y + cosf(transformParam.fAngle + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = transformParam.pos.x + sinf(transformParam.fAngle - fAngle) * fLength;
	pVtx[2].pos.y = transformParam.pos.y + cosf(transformParam.fAngle - fAngle) * fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = transformParam.pos.x + sinf(transformParam.fAngle + fAngle) * fLength;
	pVtx[3].pos.y = transformParam.pos.y + cosf(transformParam.fAngle + fAngle) * fLength;
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 色の設定
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
	if (FAILED(m_vertexBuffer.UnLock()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CObject2D::Uninit(void)
{
	// 自分自身の破棄
	Release();
}

//===================================================
// 更新処理
//===================================================
void CObject2D::Update(void)
{
}

//===================================================
// 描画処理
//===================================================
void CObject2D::Draw(void)
{
	// マネージャー
	CManager& manager = CManager::Instance();

	// レンダラーの取得
	CRenderer* pRenderer = manager.GetRenderer();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャマネージャーの取得
	CTextureManager* pTextureManager = manager.GetTextureManager();

	// 頂点バッファをバインド
	m_vertexBuffer.Bind(pDevice);

	// テクスチャを設定
	pDevice->SetTexture(0, pTextureManager->GetAdress(m_nTextureID));

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // プリミティブの種類	
}