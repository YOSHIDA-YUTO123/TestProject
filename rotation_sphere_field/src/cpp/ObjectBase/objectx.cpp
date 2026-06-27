//===================================================
//
// モデルの描画クラス [objectx.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "ObjectBase/objectx.h"
#include "Base/model_manager.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/texture_manager.h"

//===================================================
// コンストラクタ
//===================================================
CObjectX::CObjectX() :
	m_transform(),
	m_size(Const::VEC3_NULL),
	m_fAlpha(1.0f),
	m_nModelID(CModelManager::INVALID_ID)
{
}

//===================================================
// デストラクタ
//===================================================
CObjectX::~CObjectX()
{
}

//===================================================
// 生成処理
//===================================================
CObjectX* CObjectX::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* pModelFilePath)
{
	CObjectX* pInstance = new CObjectX();

	// モデルのIDの取得
	pInstance->RegisterModelID(pModelFilePath);

	Transform3D transform = {};

	transform.pos = pos;
	D3DXQuaternionRotationYawPitchRoll(&transform.quaternion, rot.y, rot.x, rot.z);

	// 情報の設定
	pInstance->m_transform.SetParam(transform);
		
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
HRESULT CObjectX::Init(void)
{
	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CObjectX::Uninit(void)
{
	// 自分自身の破棄
	Release();
}

//===================================================
// 更新処理
//===================================================
void CObjectX::Update(void)
{
	// ワールドマトリックスの計算処理
	m_transform.CalculationMatrix();
}

//===================================================
// 描画処理
//===================================================
void CObjectX::Draw(void)
{
	// マネージャーの取得
	CManager& manager = CManager::Instance();

	// レンダラーの取得
	CRenderer* pRenderer = manager.GetRenderer();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャマネージャーの取得
	CTextureManager* pTextureManager = manager.GetTextureManager();

	// モデルマネージャークラスの取得
	CModelManager* pModelManager = manager.GetModelManager();

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	// マトリックスの設定
	m_transform.BindMatrix(pDevice);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	if (m_nModelID == -1)
	{
		//保存していたマテリアルを元に戻す
		pDevice->SetMaterial(&matDef);
		return;
	}

	// モデルの情報の取得
	CModelManager::ModelInfo modelInfo = pModelManager->GetModelInfo(m_nModelID);

	// マテリアルのデータへのポインタを取得
	pMat = (D3DXMATERIAL*)modelInfo.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)modelInfo.dwNumMat; nCntMat++)
	{
		D3DXMATERIAL localMat = pMat[nCntMat];
		localMat.MatD3D.Diffuse.a = m_fAlpha;

		// マテリアルの設定
		pDevice->SetMaterial(&localMat.MatD3D);

		// 要素が無いなら
		if (modelInfo.nTextureIdx.empty())
		{
			break;
		}

		//テクスチャの設定
		pDevice->SetTexture(0, pTextureManager->GetAdress(modelInfo.nTextureIdx[nCntMat]));

		//モデル(パーツ)の描画
		modelInfo.pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
}

//===================================================
// モデルのIDの登録処理
//===================================================
void CObjectX::RegisterModelID(const char* pModelFilePath)
{
	// マネージャークラスの取得
	CManager& manager = CManager::Instance();

	// モデルマネージャークラスの取得
	CModelManager* pModelManager = manager.GetModelManager();

	// テクスチャマネージャークラスの取得
	CTextureManager* pTextureManager = manager.GetTextureManager();

	// インデックスの登録
	m_nModelID = pModelManager->Register(pModelFilePath);

	if (m_nModelID == -1)
	{
		return;
	}

	// モデルのIDの取得
	CModelManager::ModelInfo modelInfo = pModelManager->GetModelInfo(m_nModelID);

	D3DXMATERIAL* pMat;//マテリアルへのポインタ

	//マテリアルのデータへのポインタを取得
	pMat = (D3DXMATERIAL*)modelInfo.pBuffMat->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)modelInfo.dwNumMat; nCnt++)
	{
		int nTextureID = -1;

		// ファイル名を使用してテクスチャを読み込む
		nTextureID = pTextureManager->Register(pMat[nCnt].pTextureFilename);

		// テクスチャのIDの取得
		modelInfo.nTextureIdx.push_back(nTextureID);
	}

	m_size = modelInfo.size;
}