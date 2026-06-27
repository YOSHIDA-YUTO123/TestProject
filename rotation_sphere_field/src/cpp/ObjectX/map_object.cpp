//===================================================
//
// マップオブジェクト [map_object.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "ObjectX/map_object.h"
#include "Scene/title.h"
#include "ObjectX/rotation_sphere_field.h"
#include "Base/utility_math.h"
#include "System/input_system.h"
#include "Debug/debug_proc.h"


//===================================================
// コンストラクタ
//===================================================
CMapObject::CMapObject()
{
}

//===================================================
// デストラクタ
//===================================================
CMapObject::~CMapObject()
{
}

//===================================================
// 生成処理
//===================================================
CMapObject* CMapObject::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& sphereCenter, const D3DXQUATERNION& sphereQuat, const D3DXMATRIX& sphereMatrix, const char* pModelFilePath)
{
	CMapObject* pInstance = new CMapObject;

	// ワールド情報の取得
	CTransform3D* pTransform = pInstance->GetTransform();

	Transform3D transformParam = {};

	pInstance->RegisterModelID(pModelFilePath);
	pInstance->m_parentQuat = sphereQuat;

	// 中心から生成位置までの距離をオフセットとする
	pInstance->m_offset = pos - sphereCenter;
	pInstance->m_sphereCenter = sphereCenter;

	// 球体の世界情報を基準にオフセット分離れた位置に位置を設定する
	D3DXVec3TransformCoord(&transformParam.pos, &pInstance->m_offset, &sphereMatrix);

	// 親の回転を設定する
	//transformParam.quaternion = pInstance->m_parentQuat;

	pTransform->SetParam(transformParam);

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
HRESULT CMapObject::Init(void)
{
	// 初期化処理
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	//// ワールド情報の取得
	//CTransform3D* pTransform = GetTransform();

	//CTitle::GetRotationSphereField()->GetTransform()->SetChildren(pTransform);

	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CMapObject::Uninit(void)
{
	// 終了処理
	CObjectX::Uninit();
}

//===================================================
// 更新処理
//===================================================
void CMapObject::Update(void)
{
	// ワールド情報の取得
	CTransform3D* pTransform = CObjectX::GetTransform();

	// パラメータの取得
	Transform3D transformParam = pTransform->GetParam();

	// フィールドに乗って回転追従するための座標の取得
	CTitle::GetRotationSphereField()->OnRotate(transformParam, m_offset, m_parentQuat);

	// パラメータの設定
	pTransform->SetParam(transformParam);

	// 更新処理
	CObjectX::Update();
}

//===================================================
// 描画処理
//===================================================
void CMapObject::Draw(void)
{
	// 描画処理
	CObjectX::Draw();
}