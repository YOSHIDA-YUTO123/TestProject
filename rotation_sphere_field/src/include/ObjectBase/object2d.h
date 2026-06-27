//===================================================
//
// 2Dオブジェクトの描画クラス [object2d.h]
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
#include "Transform/transform2d.h"

//***************************************************
// 前方宣言
//***************************************************

//***************************************************
// 2Dオブジェクトのクラスの定義
//***************************************************
class CObject2D : public CObject
{
public:
	CObject2D();
	virtual ~CObject2D();

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="size">大きさ</param>
	/// <returns>Object2Dのポインタ</returns>
	static CObject2D* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);

	virtual HRESULT Init	(void) override;
	virtual void	Uninit	(void) override;
	virtual void	Update	(void) override;
	virtual void	Draw	(void) override;
private:
	CVertexBuffer m_vertexBuffer;	// 頂点バッファクラス
	CTransform2D m_transform;		// ワールド情報
	D3DXCOLOR m_col;				// 色
	int m_nTextureID;				// テクスチャのID
};