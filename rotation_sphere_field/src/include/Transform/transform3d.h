//===================================================
//
// 3Dのワールド情報のクラス [transform3d.h]
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
// 3Dワールド情報クラスの定義
//***************************************************
class CTransform3D
{
public:
	CTransform3D();
	~CTransform3D();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(void);

	/// <summary>
	/// ワールドマトリックスの更新処理
	/// </summary>
	/// <param name=""></param>
	void CalculationMatrix(void);

	/// <summary>
	/// ワールドマトリックスのバインド
	/// </summary>
	void BindMatrix(LPDIRECT3DDEVICE9 pDevice);

	/// <summary>
	/// パラメータの取得
	/// </summary>
	/// <returns>Transform3D構造体</returns>
	inline Transform3D GetParam(void) const { return m_param; }

	/// <summary>
	/// パラメータの設定
	/// </summary>
	/// <param name="transform3D">設定した情報</param>
	inline void SetParam(const Transform3D& transform3D) { m_param = transform3D; }

	/// <summary>
	/// 親の設定処理
	/// </summary>
	/// <param name="pParent">親のアドレス</param>
	void SetParent(CTransform3D* pParent);

	/// <summary>
	/// 子供の設定処理
	/// </summary>
	/// <param name="pChild">子供のアドレス</param>
	void SetChildren(CTransform3D* pChild);
private:
	std::vector<CTransform3D*> m_vpChildren;	// 子供のリスト
	CTransform3D* m_pParent;				// 親へのポインタ

	Transform3D m_param;					// 情報
};