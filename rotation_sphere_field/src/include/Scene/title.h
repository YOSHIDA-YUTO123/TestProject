//===================================================
//
// タイトルクラス [title.h]
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
#include "Scene/scene.h"

//***************************************************
// 前方宣言
//***************************************************
class CRotationSphereField;	// 回転フィールドクラス

//***************************************************
// タイトルのクラスの定義
//***************************************************
class CTitle : public CScene
{
public:
	static constexpr int NUM_PLANE_LINE = 10;				// 板の分割数
	const D3DXVECTOR3 PLANE_SIZE = { 2000.0f,0.0f,2000.0f };	// 板のサイズ

	CTitle();
	~CTitle();

	HRESULT Init	(void) override;
	void	Uninit	(void) override;
	void	Update	(void) override;
	void	Draw	(void) override;

	/// <summary>
	/// 回転フィールドのポインタの取得
	/// </summary>
	/// <returns>ポインタ</returns>
	static CRotationSphereField* GetRotationSphereField(void) { return m_pRotationSphereField; }

private:
	inline static CRotationSphereField* m_pRotationSphereField;	// 回転フィールドクラスへのポインタ
};