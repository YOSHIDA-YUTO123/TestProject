//===================================================
//
// キャラクター [character.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "Character/character.h"
#include "System/motion.h"
#include "Character/model.h"
#include "Base/manager.h"
#include "Base/renderer.h"

//===================================================
// コンストラクタ
//===================================================
CCharacter3D::CCharacter3D(const char* pMotionFilePath) :
	m_vpModel(),
	m_pMotion(nullptr)
{
	m_pMotion = CMotion::Load(pMotionFilePath, m_vpModel);
}

//===================================================
// デストラクタ
//===================================================
CCharacter3D::~CCharacter3D()
{
	// モデル分回す
	for (auto& model : m_vpModel)
	{
		model->Uninit();
		model.reset();
	}

	m_vpModel.clear();
}

//===================================================
// 更新処理
//===================================================
void CCharacter3D::Update(void)
{
	if (m_pMotion == nullptr)
	{
		return;
	}

	// モデルのサイズの取得
	int nNumModel = static_cast<int>(m_vpModel.size());

	// モーションの更新処理
	m_pMotion->Update(m_vpModel, nNumModel);
}

//===================================================
// 描画処理
//===================================================
void CCharacter3D::Draw(void)
{
	// モデル分回す
	for (auto& model : m_vpModel)
	{
		if (model == nullptr)
		{
			continue;
		}

		// モデルの描画処理
		model->Draw();
	}
}