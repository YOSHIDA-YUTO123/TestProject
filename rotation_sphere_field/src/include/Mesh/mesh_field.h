//===================================================
//
// メッシュの共通パラメータ [mesh_field.h]
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
#include "Transform/transform3d.h"
#include "Mesh/mesh_param.h"
#include "ObjectBase/object.h"

//***************************************************
// メッシュフィールドのクラスの定義
//***************************************************
class CMeshField : public CObject
{
public:
	CMeshField();
	~CMeshField();

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="size">大きさ</param>
	/// <param name="segment">分割数</param>
	/// <param name="pTexturePath">テクスチャのファイルパス</param>
	/// <returns>MeshFieldのポインタ</returns>
	static CMeshField* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const VECTOR2INT& segment, const char* pTexturePath);

	HRESULT Init	(void) override;
	void	Uninit	(void) override;
	void	Update	(void) override;
	void	Draw	(void) override;

	/// <summary>
	/// テクスチャのIDの設定処理
	/// </summary>
	/// <param name="pTexturePath">テクスチャのパス</param>
	void SetTextureID(const char* pTexturePath);
private:
	CTransform3D	m_transfrom;	// 空間情報
	MeshParam		m_param;		// 共通パラメータ
	D3DXVECTOR3		m_size;			// 大きさ
};