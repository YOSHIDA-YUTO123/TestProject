//===================================================
//
// インプットの情報をまとめた名前空間 [input_system.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "System/input_system.h"
#include "Base/input.h"
#include "Base/manager.h"

//===================================================
// 正面移動
//===================================================
bool InputSystem::MoveForward(void)
{
	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::Instance().GetInputKeyboard();

	// 押したかどうかを判定
	bool bFlag = pKeyboard->GetPress(DIK_W);

	return bFlag;
}

//===================================================
// 左移動
//===================================================
bool InputSystem::MoveLeft(void)
{
	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::Instance().GetInputKeyboard();

	// 押したかどうかを判定
	bool bFlag = pKeyboard->GetPress(DIK_A);

	return bFlag;
}

//===================================================
// 右移動
//===================================================
bool InputSystem::MoveRight(void)
{
	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::Instance().GetInputKeyboard();

	// 押したかどうかを判定
	bool bFlag = pKeyboard->GetPress(DIK_D);

	return bFlag;
}

//===================================================
// マップオブジェクトの生成
//===================================================
bool InputSystem::CreateMapObject(void)
{
	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::Instance().GetInputKeyboard();

	// 押したかどうかを判定
	bool bFlag = pKeyboard->GetTrigger(DIK_RETURN);

	return bFlag;
}

//===================================================
// スケーリングキー
//===================================================
InputSystem::SPHERE_SCALING InputSystem::ScalingSphere(void)
{
	SPHERE_SCALING flag = SPHERE_SCALING::MAX;

	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::Instance().GetInputKeyboard();

	// 押したかどうかを判定
	if (pKeyboard->GetPress(DIK_UP))
	{
		flag = SPHERE_SCALING::EXPAND;
	}

	// 押したかどうかを判定
	if (pKeyboard->GetPress(DIK_DOWN))
	{
		flag = SPHERE_SCALING::REDUCTION;
	}

	return flag;
}

//===================================================
// 後ろ移動
//===================================================
bool InputSystem::MoveBack(void)
{
	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::Instance().GetInputKeyboard();

	// 押したかどうかを判定
	bool bFlag = pKeyboard->GetPress(DIK_S);

	return bFlag;
}