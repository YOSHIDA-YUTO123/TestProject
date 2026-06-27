//===================================================
//
// オブジェクトの管理クラス [object_manager.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "Manager/object_manager.h"
#include "ObjectBase/object.h"
#include "Base/manager.h"
#include "Base/camera.h"

//===================================================
// オブジェクトの登録
//===================================================
void CObjectManager::Register(CObject* pObject, const int nPriority)
{
	// リストに追加する
	m_lpObject[nPriority].push_back(pObject);
}

//===================================================
// 全ての破棄
//===================================================
void CObjectManager::ReleaseAll(void)
{
	// 優先順位
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// オブジェクトのリスト分回す
		for (auto itr = m_lpObject[nCntPriority].begin(); itr != m_lpObject[nCntPriority].end();)
		{
			// nullだったら処理を飛ばす
			if ((*itr) == nullptr)
			{
				itr++;
				continue;
			}

			// 更新処理
			(*itr)->Uninit();
			delete (*itr);
			(*itr) = nullptr;
		}
	}
}

//===================================================
// 全てのオブジェクトの更新処理
//===================================================
void CObjectManager::UpdateAll(void)
{
	// 優先順位
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// オブジェクトのリスト分回す
		for (auto itr = m_lpObject[nCntPriority].begin(); itr != m_lpObject[nCntPriority].end();)
		{
			// nullだったら処理を飛ばす
			if ((*itr) == nullptr)
			{
				itr++;
				continue;
			}

			// 更新処理
			(*itr)->Update();
			itr++;
		}
	}

	// 優先順位
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// オブジェクトのリスト分回す
		for (auto itr = m_lpObject[nCntPriority].begin(); itr != m_lpObject[nCntPriority].end();)
		{
			// nullだったら処理を飛ばす
			if ((*itr) == nullptr)
			{
				itr++;
				continue;
			}

			// 死んでいないなら
			if ((*itr)->IsDeath() == false)
			{
				itr++;
				continue;
			}

			// 破棄する
			delete (*itr);
			(*itr) = nullptr;

			itr = m_lpObject[nCntPriority].erase(itr);

			// 次の要素がないなら
			if (itr == m_lpObject[nCntPriority].end())
			{
				break;
			}
		}
	}
}

//===================================================
// 全てのオブジェクトの描画処理
//===================================================
void CObjectManager::DrawAll(void)
{
	// カメラの取得
	CCamera* pCamera = CManager::Instance().GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	// カメラの設定
	pCamera->SetCamera();

	// 優先順位
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// オブジェクトのリスト分回す
		for (auto itr = m_lpObject[nCntPriority].begin(); itr != m_lpObject[nCntPriority].end();)
		{
			// nullだったら処理を飛ばす
			if ((*itr) == nullptr)
			{
				itr++;
				continue;
			}

			// 描画処理
			(*itr)->Draw();
			itr++;
		}
	}
}