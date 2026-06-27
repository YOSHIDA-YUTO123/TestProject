//===================================================
//
// モデルの描画クラス [objectx.h]
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
#include "ObjectBase/object.h"
#include "Transform/transform3d.h"

//***************************************************
// 前方宣言
//***************************************************

//***************************************************
// モデルの描画クラスの定義
//***************************************************
class CObjectX : public CObject
{
public:
	CObjectX();
	virtual ~CObjectX();

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="rot">向き</param>
	/// <param name="pModelFilePath">モデルのファイルパス</param>
	/// <returns>ObjectXのポインタ</returns>
	static CObjectX* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* pModelFilePath);

	virtual HRESULT Init	(void) override;
	virtual void	Uninit	(void) override;
	virtual void	Update	(void) override;
	virtual void	Draw	(void) override;

	/// <summary>
	/// モデルのIDの登録
	/// </summary>
	/// <param name="pModelFilePath">モデルのファイルパス</param>
	void RegisterModelID(const char* pModelFilePath);

	/// <summary>
	/// ワールド情報の取得
	/// </summary>
	/// <returns>ワールド情報のポインタ</returns>
	inline CTransform3D* GetTransform(void) { return &m_transform; }

	/// <summary>
	/// 大きさの取得処理
	/// </summary>
	/// <returns>大きさの取得</returns>
	inline D3DXVECTOR3 GetSize(void) const { return m_size; }

private:
	CTransform3D	m_transform;	// ワールド情報
	D3DXVECTOR3		m_size;			// 大きさ
	float			m_fAlpha;		// アルファ値
	int				m_nModelID;		// モデルの番号
};