//===================================================
//
// インプットの情報をまとめた名前空間 [input_system.h]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// 多重インクルード防止
//***************************************************
#pragma once

//***************************************************
// インクルードファイル
//***************************************************

//***************************************************
// インプットの情報をまとめた名前空間
//***************************************************
namespace InputSystem
{
	// 球体のスケーリング
	enum class SPHERE_SCALING
	{
		EXPAND = 0,	// 拡大
		REDUCTION,	// 縮小
		MAX
	};
	/// <summary>
	/// 正面移動キー
	/// </summary>
	/// <returns>入力している間true</returns>
	bool MoveForward(void);

	/// <summary>
	/// 後ろ移動キー
	/// </summary>
	/// <returns>入力している間true</returns>
	bool MoveBack(void);

	/// <summary>
	/// 左移動キー
	/// </summary>
	/// <returns>入力している間true</returns>
	bool MoveLeft(void);

	/// <summary>
	/// 右移動キー
	/// </summary>
	/// <returns>入力している間true</returns>
	bool MoveRight(void);

	/// <summary>
	/// マップオブジェクトの生成処理
	/// </summary>
	/// <returns>入力したらtrue</returns>
	bool CreateMapObject(void);

	/// <summary>
	/// 球体の大きさの変更キー
	/// </summary>
	/// <returns>スケーリングの状態</returns>
	SPHERE_SCALING ScalingSphere(void);
}