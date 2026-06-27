//===================================================
//
// メッシュの共通パラメータ [mesh_field.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "Mesh/mesh_field.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/texture_manager.h"

//===================================================
// コンストラクタ
//===================================================
CMeshField::CMeshField() : 
	m_transfrom(),
	m_param(),
	m_size(Const::VEC3_NULL)
{
}

//===================================================
// デストラクタ
//===================================================
CMeshField::~CMeshField()
{
}

//===================================================
// 生成処理
//===================================================
CMeshField* CMeshField::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const VECTOR2INT& segment, const char* pTexturePath)
{
	// メッシュフィールドの生成
	CMeshField* pInstance = new CMeshField;

	Transform3D transformParam = {};
	transformParam.pos = pos;
	
	// パラメータの設定
	pInstance->m_transfrom.SetParam(transformParam);
	pInstance->m_param.segment = segment;
	pInstance->m_size = size;

	// テクスチャのIDの設定
	pInstance->SetTextureID(pTexturePath);

	// 初期化処理
	if (FAILED(pInstance->Init()))
	{
		pInstance->Uninit();
		pInstance = nullptr;
		return nullptr;
	}

	return pInstance;
}

//===================================================
// 初期化処理
//===================================================
HRESULT CMeshField::Init(void)
{
	// 頂点数の設定
	m_param.nNumVertex = (m_param.segment.x + 1) * (m_param.segment.y + 1);

	// ポリゴン数の設定
	m_param.nNumPolygon = ((m_param.segment.x * m_param.segment.y) * 2) + (4 * (m_param.segment.y - 1));

	// インデックス数の設定
	m_param.nNumIndex = m_param.nNumPolygon + 2;

	// 頂点バッファの生成
	HRESULT hr = m_param.vertexBuffer.CreateBuffer(sizeof(VERTEX_3D), m_param.nNumVertex, FVF_VERTEX_3D);

	// 生成失敗
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// インデックスバッファの生成
	hr = m_param.indexBuffer.Create(m_param.nNumIndex);

	// 頂点のカウント
	int nCntVtx = 0;

	// テクスチャの座標の割合
	float fTexPosX = 1.0f / m_param.segment.x;
	float fTexPosY = 1.0f / m_param.segment.y;

	// 計算用の位置
	D3DXVECTOR3 posWk;

	VERTEX_3D* pVtx = nullptr;

	// パラメータの取得
	Transform3D transformParam = m_transfrom.GetParam();

	// 頂点バッファをロック
	m_param.vertexBuffer.Lock((void**)&pVtx);

	// 縦の分割数
	for (int nCntV = 0; nCntV <= m_param.segment.y; nCntV++)
	{
		for (int nCntU = 0; nCntU <= m_param.segment.x; nCntU++)
		{
			// 位置の設定
			posWk.x = ((m_size.x / m_param.segment.x) * nCntU) - (m_size.x * 0.5f);
			posWk.y = transformParam.pos.y;
			posWk.z = m_size.z - ((m_size.z / m_param.segment.y) * nCntV) - (m_size.z * 0.5f);

			pVtx[nCntVtx].pos = posWk;

			//法線ベクトルの設定
			pVtx[nCntVtx].nor = Const::VEC_U;

			//頂点カラーの設定
			pVtx[nCntVtx].col = m_param.col;

			//テクスチャ座標の設定
			pVtx[nCntVtx].tex = D3DXVECTOR2((fTexPosX * nCntU), (fTexPosY * nCntV));

			nCntVtx++;
		}
	}

	// 頂点バッファをアンロック
	m_param.vertexBuffer.UnLock();

	// インデックスバッファへのポインタ
	WORD* pIdx;

	// インデックスバッファのロック
	m_param.indexBuffer.Lock((void**)&pIdx);

	int IndxNum = m_param.segment.x + 1;	// X

	int IdxCnt = 0;					// 配列

	int nNum = 0;					//

	//インデックスの設定
	for (int IndxCount1 = 0; IndxCount1 < m_param.segment.y; IndxCount1++)
	{
		for (int IndxCount2 = 0; IndxCount2 <= m_param.segment.x; IndxCount2++, IndxNum++, nNum++)
		{
			// インデックスバッファの設定
			pIdx[IdxCnt] = static_cast<WORD>(IndxNum);
			pIdx[IdxCnt + 1] = static_cast<WORD>(nNum);
			IdxCnt += 2;
		}

		// NOTE:最後の行じゃなかったら
		if (IndxCount1 < m_param.segment.y - 1)
		{
			pIdx[IdxCnt] = static_cast<WORD>(nNum - 1);
			pIdx[IdxCnt + 1] = static_cast<WORD>(IndxNum);
			IdxCnt += 2;
		}
	}

	// インデックスバッファのアンロック
	m_param.indexBuffer.UnLock();

	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CMeshField::Uninit(void)
{
	// 自分自身の破棄
	Release();
}

//===================================================
// 更新処理
//===================================================
void CMeshField::Update(void)
{
}

//===================================================
// 描画処理
//===================================================
void CMeshField::Draw(void)
{
	// マネージャーの取得
	CManager& manager = CManager::Instance();

	// レンダラーの取得
	CRenderer* pRenderer = manager.GetRenderer();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャマネージャーの取得
	CTextureManager* pTextureManager = manager.GetTextureManager();

	// ワールドマトリックスの設定
	m_transfrom.BindMatrix(pDevice);

	// インデックスバッファをデータストリームに設定
	m_param.indexBuffer.Bind(pDevice);

	// ストリームソースの設定、フォーマットの設定
	m_param.vertexBuffer.Bind(pDevice);

	// テクスチャの設定
	pDevice->SetTexture(0, pTextureManager->GetAdress(m_param.nTextureID));

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_param.nNumVertex, 0, m_param.nNumPolygon);
}

//===================================================
// テクスチャのIDの設定
//===================================================
void CMeshField::SetTextureID(const char* pTexturePath)
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
	m_param.nTextureID = pTextureManager->Register(pTexturePath);
}
