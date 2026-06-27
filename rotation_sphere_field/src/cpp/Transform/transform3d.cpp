//===================================================
//
// 3Dのワールド情報のクラス [transform3d.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "Transform\transform3d.h"

//===================================================
// コンストラクタ
//===================================================
CTransform3D::CTransform3D() : 
	m_param(),
	m_vpChildren(),
	m_pParent(nullptr)
{
}

//===================================================
// デストラクタ
//===================================================
CTransform3D::~CTransform3D()
{
}

//===================================================
// 更新処理
//===================================================
void CTransform3D::Update(void)
{

}

//===================================================
// ワールドマトリックスの更新処理
//===================================================
void CTransform3D::CalculationMatrix(void)
{
	// 計算用マトリックス
	D3DXMATRIX mtxTrans, mtxScal;

	// マトリックスの初期化
	m_param.mtxWorld = Const::MTX_IDENTITY;

	// スケールの作成
	D3DXMatrixScaling(&mtxScal, m_param.scale.x, m_param.scale.y, m_param.scale.z);

	// スケールを掛け合わせる
	m_param.mtxWorld *= mtxScal;

	// 回転行列の作成
	D3DXMatrixRotationQuaternion(&m_param.mtxRotation, &m_param.quaternion);

	// 回転を掛け合わせる
	m_param.mtxWorld *= m_param.mtxRotation;

	// 平行移動行列の生成
	D3DXMatrixTranslation(&mtxTrans, m_param.pos.x, m_param.pos.y, m_param.pos.z);

	// 行列を掛け合わせる
	m_param.mtxWorld *= mtxTrans;

	if (m_pParent != nullptr)
	{
		// 親とマトリックスを掛け合わせる
		m_param.mtxWorld *= m_pParent->m_param.mtxWorld;
	}
}

//===================================================
// ワールドマトリックスのバインド
//===================================================
void CTransform3D::BindMatrix(LPDIRECT3DDEVICE9 pDevice)
{
	// ワールドマトリックスの設定処理
	pDevice->SetTransform(D3DTS_WORLD, &m_param.mtxWorld);
}

//===================================================
// 親の設定処理
//===================================================
void CTransform3D::SetParent(CTransform3D* pParent)
{
	m_pParent = pParent;

	if (m_pParent != nullptr)
	{
		// 親の子供を自分にする
		m_pParent->SetChildren(this);
	}
}

//===================================================
// 子供の設定
//===================================================
void CTransform3D::SetChildren(CTransform3D* pChild)
{
	// すでに追加されているか確認
	auto itr = std::find(m_vpChildren.begin(), m_vpChildren.end(), pChild);

	if (itr == m_vpChildren.end())
	{
		if (pChild != nullptr)
		{
			// 子供の追加
			m_vpChildren.push_back(pChild);

			// 子供の親を自分にする
			pChild->SetParent(this);
		}
	}
}