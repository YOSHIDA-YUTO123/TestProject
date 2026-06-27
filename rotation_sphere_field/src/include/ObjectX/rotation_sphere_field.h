//===================================================
//
// 回転する球体のステージ [rotation_sphere_field.h]
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
#include "ObjectBase/objectx.h"

//***************************************************
// 前方宣言
//***************************************************

//***************************************************
// 回転する球体のステージのクラスの定義
//***************************************************
class CRotationSphereField : public CObjectX
{
public:
	CRotationSphereField();
	~CRotationSphereField();

	/// <summary>
	/// 生成胥吏
	/// </summary>
	/// <param name="pos">位置</param>
	/// <returns>CRotationSphereFieldのポインタ</returns>
	static CRotationSphereField* Create(const D3DXVECTOR3& pos);

	HRESULT Init	(void) override;
	void	Uninit	(void) override;
	void	Update	(void) override;
	void	Draw	(void) override;

	/// <summary>
	/// 半径の取得処理
	/// </summary>
	/// <returns>半径</returns>
	inline float GetRadius(void) const { return m_fRadius; }

	/// <summary>
	/// 上に乗せる
	/// </summary>
	/// <returns>頂点の位置</returns>
	D3DXVECTOR3 OnTopPosition(void);

	/// <summary>
	/// 回転後の姿勢、位置の取得
	/// </summary>
	/// <returns>回転後の姿勢、位置</returns>
	void OnRotate(Transform3D& transform, const D3DXVECTOR3& offset, const D3DXQUATERNION& offsetQuat);
private:
	/// <summary>
	/// キーボードの移動
	/// </summary>
	void KeyboardMove(void);

	/// <summary>
	/// 回転の計算
	/// </summary>
	void CalculationRotationQuaternion(void);
private:
	D3DXMATRIX m_baseMatrixWorld;	// 基準となるマトリックス
	D3DXVECTOR3 m_dir;				// 移動方向
	float m_fCircumference;			// 円周の大きさ
	float m_fRadius;				// 半径
	float m_fAngleValue;			// 回転量
};