//===================================================
//
// 3Dオブジェクトの描画クラス [object3d.h]
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
#include "Buffer/vertex_buffer.h"
#include "Transform/transform3d.h"

//***************************************************
// 前方宣言
//***************************************************

//***************************************************
// 3Dオブジェクトのクラスの定義
//***************************************************
class CObject3D : public CObject
{
public:
	CObject3D();
	virtual ~CObject3D();

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="size">大きさ</param>
	/// <returns>Object3Dのポインタ</returns>
	static CObject3D* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const char* pTexturePath);

	virtual HRESULT Init	(void) override;
	virtual void	Uninit	(void) override;
	virtual void	Update	(void) override;
	virtual void	Draw	(void) override;

	/// <summary>
	/// テクスチャのIDの設定処理
	/// </summary>
	/// <param name="pTexturePath">テクスチャのパス</param>
	void SetTextureID(const char* pTexturePath);
private:
	CVertexBuffer m_vertexBuffer;	// 頂点バッファクラス
	CTransform3D m_transform;		// ワールド情報
	D3DXCOLOR m_col;				// 色
	D3DXVECTOR3 m_size;				// 大きさ
	int m_nTextureID;				// テクスチャのID
};