//===================================================
//
// 2Dのワールド情報のクラス [transform2d.h]
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
#include "Transform/transform_data.h"

//***************************************************
// 2Dワールドクラスの定義
//***************************************************
class CTransform2D
{
public:
	CTransform2D();
	~CTransform2D();

	/// <summary>
	/// パラメータ
	/// </summary>
	/// <returns>情報</returns>
	inline Transform2D GetParam(void) const { return m_param; }

	/// <summary>
	/// パラメータの設定
	/// </summary>
	/// <param name="param">新しく設定したい情報</param>
	inline void SetParam(const Transform2D& param) { m_param = param; }
private:
	Transform2D m_param;	// 情報
};